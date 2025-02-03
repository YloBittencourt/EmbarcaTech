#include <stdio.h>
#include "pico/stdlib.h"
#include <hardware/pio.h>
#include "hardware/clocks.h"
#include "hardware/gpio.h"

//arquivo .pio
#include "led.pio.h"

//Variáveis Globais
PIO pio;
uint sm;

//constantes de escopo global
const uint led_pin_red = 13; 
const uint botaoA = 5;
const uint botaoB = 6;

static volatile uint num = 0;
static volatile uint32_t ultima = 0;

double led[10][25] = {
        {0, 1, 1, 1, 0,
         0, 1, 0, 1, 0,
         0, 1, 0, 1, 0,
         0, 1, 0, 1, 0,
         0, 1, 1, 1, 0,
        }, // 0
        {0, 0, 1, 0, 0,
         0, 1, 1, 0, 0,
         0, 0, 1, 0, 0,
         0, 0, 1, 0, 0,
         0, 1, 1, 1, 0,
        }, // 1
        {0, 1, 1, 1, 0,
         0, 0, 0, 1, 0,
         0, 1, 1, 1, 0,
         0, 1, 0, 0, 0,
         0, 1, 1, 1, 0,
        },  // 2
        {0, 1, 1, 1, 0,
         0, 0, 0, 1, 0,
         0, 1, 1, 1, 0,
         0, 0, 0, 1, 0,
         0, 1, 1, 1, 0,
        }, // 3
        {0, 1, 0, 1, 0,
         0, 1, 0, 1, 0,
         0, 1, 1, 1, 0,
         0, 0, 0, 1, 0,
         0, 0, 0, 1, 0,
        }, // 4
        {0, 1, 1, 1, 0,
         0, 1, 0, 0, 0,
         0, 1, 1, 1, 0,
         0, 0, 0, 1, 0,
         0, 1, 1, 1, 0,
        }, // 5
        {0, 1, 1, 1, 0,
         0, 1, 0, 0, 0,
         0, 1, 1, 1, 0,
         0, 1, 0, 1, 0,
         0, 1, 1, 1, 0,
        },  // 6
        {0, 1, 1, 1, 0,
         0, 0, 0, 1, 0,
         0, 0, 1, 0, 0,
         0, 0, 1, 0, 0,
         0, 0, 1, 0, 0,
        }, // 7
        {0, 1, 1, 1, 0,
         0, 1, 0, 1, 0,
         0, 1, 1, 1, 0,
         0, 1, 0, 1, 0,
         0, 1, 1, 1, 0,
        }, // 8
        {0, 1, 1, 1, 0,
         0, 1, 0, 1, 0,
         0, 1, 1, 1, 0,
         0, 0, 0, 1, 0,
         0, 1, 1, 1, 0,
        }  // 9
    };

// Melhorar a intensidade
uint32_t cores(double vermelho)
{
  unsigned char R;
  R = vermelho * 100; 
  return (R << 16);
}

int sequencia[25] = {
    0, 1, 2, 3, 4,
    9, 8, 7, 6, 5,
    10, 11, 12, 13, 14,
    19, 18, 17, 16, 15,
    20, 21, 22, 23, 24
};

// Converte os valores da matriz de LEDs para a matriz de LEDs da PIO
void display_num(int number) {
    for (int i = 0; i < 25; i++) {
        uint32_t valor_led = cores(led[number][sequencia[24 - i]]);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

// Função de interrupção
static void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());

    // Debounce: evita múltiplas leituras em um curto intervalo de tempo
    if (tempo_atual - ultima > 200) {
        if (gpio == botaoA || gpio == botaoB) {
            printf("Botão %c foi acionado\n", (gpio == botaoA) ? 'A' : 'B');

            // Atualiza o número conforme o botão pressionado
            num = (gpio == botaoA) ? (num + 1) % 10 : (num + 9) % 10;
            
            printf("num = %u\n", num);

            // Atualiza o display da matriz de LEDs
            display_num(num);
            
            // Registra o tempo do último evento
            ultima = tempo_atual;
        }
    }
}

int main()
{
    pio = pio0;

    bool ok;

    // Define o clock para 128 MHz, facilitando a divisão pelo clock
    ok = set_sys_clock_khz(128000, false);

    // Inicializa todos os códigos stdio padrão que estão ligados ao binário.
    stdio_init_all();

    printf("iniciando a transmissão PIO");
    if (ok) printf("clock set to %ld\n", clock_get_hz(clk_sys));

    //configurações da PIO
    uint offset = pio_add_program(pio, &led_program);
    uint sm = pio_claim_unused_sm(pio, true);
    led_program_init(pio, sm, offset, 7);


    gpio_init(led_pin_red); //inicializa a porta 13 do microcontrolador
    gpio_set_dir(led_pin_red, GPIO_OUT); //configura a porta como saída

    gpio_init(botaoA); //inicializa a porta 5 do microcontrolador
    gpio_set_dir(botaoA, GPIO_IN); //configura a porta como entrada
    gpio_pull_up(botaoA); //configura o resistor de pull-up

    gpio_init(botaoB); //inicializa a porta 6 do microcontrolador
    gpio_set_dir(botaoB, GPIO_IN); //configura a porta como entrada
    gpio_pull_up(botaoB); //configura o resistor de pull-up

    gpio_set_irq_enabled_with_callback(botaoA, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(botaoB, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    display_num(0);

// Loop principal
while (true) {
    for (int i = 0; i < 5; i++) {
        gpio_put(led_pin_red, i % 2);  // Alterna entre ligado (1) e desligado (0)
        sleep_ms(100);
    }
    gpio_put(led_pin_red, false);  // Garante que o LED fique apagado no final
}

}