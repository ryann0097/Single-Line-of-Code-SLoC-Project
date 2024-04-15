# Introduction

O programa "sloc" ou Single Line of Code, como preferir chamá-lo, é uma útil ferramenta para métrica padrão de software usada para medir o tamanho de um programa de computador. Essas informações podem ser usadas, por exemplo, para medir objetivamente o esforço de programação feito por uma equipe de desenvolvedores, bem como para estimar as práticas de documentação de software calculando a porcentagem de comentários em um determinado projeto. O presente "sloc" tem suporte para a linguagem C/C++, recebendo um arquivo ou arquivos do diretório raiz (ainda teremos uma atualização para buscar mais arquivos),
e retornando seu nome, linguagem (C ou C++), linhas de comentário, linhas em branco e linhas de código, bem como sua soma. 

**Funcionalidades Principais**

- Estatísticas Detalhadas: Para cada arquivo analisado, o slocpp calcula o número de linhas de código, comentários e linhas em branco. Ele fornece uma visão detalhada dessas estatísticas, permitindo uma compreensão abrangente da estrutura e complexidade do código.

- Opções de Ordenação: O programa oferece opções para ordenar os resultados com base em diferentes critérios, como nome do arquivo, tipo de arquivo, número de comentários, número de linhas em branco e número total de linhas de código. Isso permite aos usuários visualizar os resultados de forma mais organizada e relevante para suas necessidades.


# Author(s) 

**Ryan David dos Santos Silvestre**

# Problems found or limitations

**Limitações:**
Como limitação principal, o "sloc" carece de uma recursão em diretório, o que indica que ele não consegue verificar arquivos fora da pasta raiz.
Outrossim, caso o usuário o mova para outras pastas, o funcionamento se dá de maneira perfeita.

# Compiling and Runnig

A compilação pode ser feita da seguinte maneira:

_"g++ -o sloc main.cpp"_ -- sendo _"g++"_ o compilador, _"sloc"_ o nome do executável (pode ser o nome de sua preferência) e
_"main.cpp"_ o arquivo fonte C++.

Para "rodar" o programa, coloque o arquivo/diretório após o nome do seu executável, seguindo as instruções.

