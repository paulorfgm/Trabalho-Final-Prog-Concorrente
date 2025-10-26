# Trabalho Final de Programação Concorrente
---

Este repositório contém a implementação do trabalho final de programação concorrente. Ele é dividido nas seguintes pastas:

- Assets: contém alguns arquivos extras para realização do trabalho, como os pdfs dos relatórios
- Bin: pasta com todos os executáveis (não é enviada para o github, estando no gitignore)
- Include: inclui todos os headers .h
- Src: inclui todos os arquivos de código .c
- Tests: inclui os arquivos .txt que representam a entrada ou saída de testes realizados
- Scripts: pasta com 4 scripts:
  - run_concorrente.sh -> executa uma implementação do BFS Concorrente, passando como argumentos a quantidade de threads e o nome do arquivo de entrada
  - run_sequencial.sh -> executa uma implementação do BFS Sequencial, passando como argumento o nome do arquivo de entrada
  - testes_corretude.sh -> executa uma série de testes de corretude, e salva sua execução em um arquivo
  - testes_perfomance.sh -> executa 4 séries de testes de performance, e salva cada uma das execuções em um arquivo