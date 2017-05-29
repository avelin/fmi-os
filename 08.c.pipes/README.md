## Системни примитиви на C за работа с pipe-ове

* `fork` -- the child inherits copies of the parent's set of open file descriptors
* T1 - Да се напише програма на C, която приема аргумент - име на файл. Програмата да:
	* записва във файла 'fo'
	* създава child процес, който записва 'bar\n'
	* parent-а, след като изчака child процеса, записва 'o\n'
* pipe(7)
* pipe(2) `int pipe(int pipefd[2]);`

* T2 - Напишете програма на C, която демонстрира комуникация през pipe между parent и child процеси. Parent-ът трябва да изпраща стринга, получен като първи аргумент на командния ред към child-а, който да го отпечатва на стандартния изход.

* mkfifo(3) `int mkfifo(const char * pathname, mode_t mode);`
* dup(2) `int dup(int oldfd);`
* dup2(2) `int dup2(int oldfd, int newfd);`

* T3 - Напишете програма на C, която демонстрира употребата на dup/dup2 между parent и child процеси. Parent-ът трябва да изпраща стринга, получен като първи аргумент на командния ред към child-а, където той да може да се чете от stdin. Child процесът да изпълнява`wc -c`.
