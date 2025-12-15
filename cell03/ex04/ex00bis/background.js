$(document).ready(function() {
    // Seleciona o botão de mudança de background
    const $changeBgButton = $('#change-bg-btn');

    // Define a cor inicial do body como azul
    $('body').css('background-color', '#007bff');

    // Função para alternar entre as cores azul e verde
    $changeBgButton.on('click', function() {
        // Verifica a cor atual do body
        const currentColor = $('body').css('background-color');

        // Alterna entre azul e verde
        if (currentColor === 'rgb(0, 123, 255)' || currentColor === '#007bff') {
            $('body').css('background-color', '#28a745'); // Verde
            $changeBgButton.css('background-color', '#007bff'); // Botão azul quando fundo verde
        } else {
            $('body').css('background-color', '#007bff'); // Azul
            $changeBgButton.css('background-color', '#28a745'); // Botão verde quando fundo azul
        }
    });

    // Estiliza o botão quando o fundo é verde
    $('body[style*="background-color: rgb(40, 167, 69)"]').find('#change-bg-btn').css('background-color', '#007bff');
});
