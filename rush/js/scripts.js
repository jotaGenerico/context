// Aguarda o documento estar completamente carregado
$(document).ready(function () {

    // 1. Rolagem Suave (Smooth Scrolling)
    // Anima a rolagem da página quando um link da navegação ou dropdown é clicado.
    $('.navbar-nav a[href^="#"], .dropdown-item[href^="#"]').on('click', function (e) {
        if (this.hash !== '') {
            e.preventDefault();

            const hash = this.hash;
            const target = $(hash);

            if (target.length) {
                $('html, body').animate({
                    scrollTop: target.offset().top - 80 // Ajusta a posição para a barra de navegação fixa
                }, 800, function () {
                    window.location.hash = hash;
                });
            }
        }
    });

    // 2. Animação de Barra de Navegação ao Rolar
    // Adiciona uma classe para mudar a aparência da barra de navegação quando o usuário rola a página.
    $(window).scroll(function() {
        if ($(this).scrollTop() > 50) {
            $('.navbar').addClass('scrolled');
        } else {
            $('.navbar').removeClass('scrolled');
        }
    });

    // 3. Efeito de Aparecer (Fade-in on Scroll)
    // Faz com que elementos com a classe '.fade-in' apareçam suavemente quando entram na tela.
    function fadeInOnScroll() {
        $('.fade-in').each(function () {
            const elementTop = $(this).offset().top;
            const elementBottom = elementTop + $(this).outerHeight();
            const viewportTop = $(window).scrollTop();
            const viewportBottom = viewportTop + $(window).height();

            if (elementBottom > viewportTop && elementTop < viewportBottom) {
                $(this).addClass('visible');
            }
        });
    }

    // Adiciona a classe 'fade-in' para os elementos que você quer animar.
    $('.card, .bio-content, .social-links').addClass('fade-in');

    // Executa a função de fade-in na rolagem e ao carregar a página.
    $(window).scroll(fadeInOnScroll);
    fadeInOnScroll();

    // 4. Fechar Menu Mobile ao Clicar em um Link
    // Fecha o menu de navegação responsivo após um item ser clicado.
    $('.navbar-nav .nav-link, .dropdown-item').on('click', function() {
        $('.navbar-collapse').collapse('hide');
    });

    // 5. Adicionar estado "ativo" aos links da navbar
    // Adiciona a classe 'active' ao link da navbar da seção visível na tela.
    $(window).scroll(function() {
        const scrollPos = $(document).scrollTop() + 100;

        $('.navbar-nav .nav-link[href^="#"]').each(function() {
            const currLink = $(this);
            const refElement = $(currLink.attr('href'));

            if (refElement.length && refElement.position().top <= scrollPos && refElement.position().top + refElement.height() > scrollPos) {
                $('.navbar-nav .nav-link').removeClass('active');
                currLink.addClass('active');
            }
        });
    });
});
