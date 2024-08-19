# Mapeamento de Arquivos em Memória Virtual com C

Este repositório contém um programa em C que realiza a leitura de um arquivo, mapeia seu conteúdo em memória virtual, e exibe os dados lidos. O objetivo deste projeto é demonstrar técnicas de manipulação de arquivos e uso de memória mapeada.

## Funcionamento

### 1. Verificação de Argumentos de Entrada

O programa exige que o usuário forneça o nome de um arquivo como argumento de linha de comando. Se o argumento não for fornecido, o programa exibirá uma mensagem de uso e encerrará a execução com um código de erro.

```c
if (argc < 2) {
    fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    exit(EXIT_FAILURE);
}
```

### 2. Abertura do Arquivo

O arquivo especificado é aberto em modo de leitura. Caso ocorra um erro ao abrir o arquivo, o programa exibirá uma mensagem de erro e encerrará a execução.

```c
int fd = open(input_file, O_RDONLY);
if (fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
}
```

### 3. Obtendo o Tamanho do Arquivo

Após abrir o arquivo, o programa obtém o seu tamanho utilizando a função fstat. Se a operação falhar, o programa exibirá uma mensagem de erro, fechará o arquivo, e encerrará a execução.

```c
struct stat file_stat;
if (fstat(fd, &file_stat) == -1) {
    perror("fstat");
    close(fd);
    exit(EXIT_FAILURE);
}
size_t file_size = file_stat.st_size;
```


### 4. Mapeamento da Memória

O conteúdo do arquivo é mapeado para uma região de memória virtual. A memória é mapeada de forma anônima e privada, permitindo leitura e escrita. Se o mapeamento falhar, o programa exibirá uma mensagem de erro, fechará o arquivo, e encerrará a execução.

```c
void *mapped_mem = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
if (mapped_mem == MAP_FAILED) {
    perror("mmap");
    close(fd);
    exit(EXIT_FAILURE);
}
```


### 5. Leitura e Cópia para a Memória Mapeada

O programa lê o conteúdo do arquivo e o copia para a memória mapeada. Em caso de falha na leitura, o programa exibirá uma mensagem de erro, desmapeará a memória, fechará o arquivo, e encerrará a execução.

```c
ssize_t bytes_read = read(fd, mapped_mem, file_size);
if (bytes_read == -1) {
    perror("read");
    munmap(mapped_mem, file_size);
    close(fd);
    exit(EXIT_FAILURE);
}
```


### 6. Exibição dos Dados

O conteúdo lido do arquivo, agora armazenado na memória mapeada, é exibido no console. Além disso, o programa mostra o tamanho dos dados lidos e o endereço de memória onde esses dados foram armazenados.

```c
printf("Data written to virtual memory:\n%.*s\n", (int)file_size, (char *)mapped_mem);
printf("Data written to virtual memory:\n%d %p\n", (int)file_size, mapped_mem);
```

### 7. Desmapeamento da Memória e Encerramento

Após a exibição dos dados, a memória mapeada é desmapeada e o arquivo é fechado. Se o desmapeamento falhar, uma mensagem de erro é exibida, mas o programa continua sua execução normalmente.

```c
if (munmap(mapped_mem, file_size) == -1) {
    perror("munmap");
}
close(fd);
```

## Exemplo de Execução

```bash
./mapeamento_arquivo exemplo.txt
Data written to virtual memory:
Hello, World!
Data written to virtual memory:
13 0x7fffe13f3000
```

## Requisitos

- Sistema operacional Unix-like (Linux, macOS).
- Compilador C (como GCC).