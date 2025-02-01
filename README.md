# EmbarcaTech
<h2>Objetivos</h2>
<p>• Compreender o funcionamento e a aplicação de interrupções em microcontroladores.</p>
<p>• Identificar e corrigir o fenômeno do bouncing em botões por meio de debouncing via software.</p>
<p>• Manipular e controlar LEDs comuns e LEDs endereçáveis WS2812.</p>
<p>• Fixar o estudo do uso de resistores de pull-up internos em botões de acionamento.</p>
<p>• Desenvolver um projeto funcional que combine hardware e software.</p>


<h2>Descrição do Projeto:</h2>
Neste projeto, você deverá utilizar os seguintes componentes conectados à placa BitDogLab:
<p>• Matriz 5x5 de LEDs (endereçáveis) WS2812, conectada à GPIO 7.</p>
<p>• LED RGB, com os pinos conectados às GPIOs (11, 12 e 13).</p>
<p>• Botão A conectado à GPIO 5.</p>
<p>• Botão B conectado à GPIO 6.</p>


<h2>Funcionalidades do Projeto</h2>
<p>1. O LED vermelho do LED RGB deve piscar continuamente 5 vezes por segundo.</p>
<p>2. O botão A deve incrementar o número exibido na matriz de LEDs cada vez que for pressionado.</p>
<p>3. O botão B deve decrementar o número exibido na matriz de LEDs cada vez que for pressionado.</p>
<p>4. Os LEDs WS2812 devem ser usados para criar efeitos visuais representando números de 0 a 9.</p>
<p>• Formatação fixa: Cada número deve ser exibido na matriz em um formato fixo, como
caracteres em estilo digital (ex.: segmentos iluminados que formem o número).</p>
<p>• Alternativamente, é permitido utilizar um estilo criativo, desde que o número seja claramente
identificável.</p>


<h2>Requisitos do Projeto</h2>
Para o desenvolvimento, devem ser seguidos os seguintes requisitos:
<p>1. Uso de interrupções: Todas as funcionalidades relacionadas aos botões devem ser implementadas
utilizando rotinas de interrupção (IRQ).</p>
<p>2. Debouncing: É obrigatório implementar o tratamento do bouncing dos botões via software.</p>
<p>3. Controle de LEDs: O projeto deve incluir o uso de LEDs comuns e LEDs WS2812, demonstrando o
domínio de diferentes tipos de controle.</p>
<p>4. Organização do código: O código deve estar bem estruturado e comentado para facilitar o
entendimento.</p>