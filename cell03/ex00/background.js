// Seleciona o botão de mudança de background
const changeBgButton = document.getElementById('change-bg-btn');

// Função para alternar entre as cores azul e verde
changeBgButton.addEventListener('click', function() {
    // Verifica a cor atual do body
    const currentColor = document.body.style.backgroundColor;

    // Alterna entre azul e verde
    if (currentColor === 'rgb(0, 123, 255)' || currentColor === '#007bff') {
        document.body.style.backgroundColor = '#28a745'; // Verde
        changeBgButton.style.backgroundColor = '#007bff'; // Botão azul quando fundo verde
    } else {
        document.body.style.backgroundColor = '#007bff'; // Azul
        changeBgButton.style.backgroundColor = '#28a745'; // Botão verde quando fundo azul
    }
});

// Define a cor inicial do body como azul ao carregar a página
document.body.style.backgroundColor = '#007bff';
