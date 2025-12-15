// todo.js

// Função para criar um cookie
function criarCookie(nome, valor, dias) {
    let data = new Date();
    data.setTime(data.getTime() + (dias * 24 * 60 * 60 * 1000));
    let expires = "expires=" + data.toUTCString();
    document.cookie = nome + "=" + valor + ";" + expires + ";path=/";
}

// Função para ler um cookie
function lerCookie(nome) {
    let nomeEQ = nome + "=";
    let cookies = document.cookie.split(';');
    for (let i = 0; i < cookies.length; i++) {
        let cookie = cookies[i];
        while (cookie.charAt(0) === ' ') {
            cookie = cookie.substring(1);
        }
        if (cookie.indexOf(nomeEQ) === 0) {
            return cookie.substring(nomeEQ.length, cookie.length);
        }
    }
    return null;
}

// Função para deletar um cookie
function deletarCookie(nome) {
    document.cookie = nome + "=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;";
}

// Função para adicionar uma nova tarefa
function adicionarTarefa() {
    let novaTarefa = prompt("Digite a nova tarefa:");
    if (novaTarefa !== null && novaTarefa.trim() !== "") {
        // Cria um elemento de tarefa
        let divTarefa = $('<div></div>').text(novaTarefa).addClass('task');
        divTarefa.click(function() {
            if (confirm(`Deseja realmente remover a tarefa "${novaTarefa}"?`)) {
                $(this).remove();
                salvarListaTarefas();
            }
        });

        // Adiciona a nova tarefa no topo da lista
        $('#ft_list').prepend(divTarefa);

        // Salva a lista de tarefas nos cookies
        salvarListaTarefas();
    }
}

// Função para salvar a lista de tarefas nos cookies
function salvarListaTarefas() {
    let tarefas = [];
    $('.task').each(function() {
        tarefas.push($(this).text());
    });
    criarCookie('listaTarefas', JSON.stringify(tarefas), 30); // Salva por 30 dias
}

// Função para carregar a lista de tarefas salva nos cookies
function carregarListaTarefas() {
    let listaTarefas = lerCookie('listaTarefas');
    if (listaTarefas) {
        listaTarefas = JSON.parse(listaTarefas);
        for (let i = 0; i < listaTarefas.length; i++) {
            let divTarefa = $('<div></div>').text(listaTarefas[i]).addClass('task');
            divTarefa.click(function() {
                if (confirm(`Deseja realmente remover a tarefa "${listaTarefas[i]}"?`)) {
                    $(this).remove();
                    salvarListaTarefas();
                }
            });
            $('#ft_list').append(divTarefa);
        }
    }
}

// Carrega a lista de tarefas ao iniciar a página
$(document).ready(function() {
    carregarListaTarefas();
});

// Ajuste de estilo para aumentar o espaço entre os itens da lista de tarefas
$('#ft_list').css('margin-top', '10px');
