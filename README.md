Цель работы: научится работать с файлами, используя функции стандартной библиотеки С

Задание:
Имеется файл с программой на языке С. Необходимо удалить из него все комментарии и записать в новый файл.

Пояснения и особенности реализации:
1) Файл с программой может быть очень большим. Поэтому НЕЛЬЗЯ весь файл заранее считать в массив.
2) Комментарии могут быть однострочными и многострочными. При этом однострочный комментарий также может состоять из нескольких строк, если он переносится на след. строку с помощью символа "обратный слэш" - "\"
3) В языке С нет вложенных комментариев
4) Комментарии внутри строковых констант не учитываются
5) Файл не обязательно представляет из себя правильную программу на С. Например, комментарий может обрываться, не закрывшись
6) Допускается как появление вместо удаленного комментария нескольких новых пробелов и/или переводов строк, так и отсутствие некоторых существующих незначащих символов-разделителей.
7) Не допускается удаление данных из константных строк, обозначенных кавычками (двойными и одинарными).

Входные и выходные данные:
Исходный файл всегда имеет имя test.c. Выходной файл должен называться test.wc.

Пример:
Данные входного файла "test.c":

int myproc1()

{

   const char* nc = " Don't touch text /* inside */ quoted strings ";



   // This is comment

   printf(" This is // not comment ");

   

   printf(" This is /* not comment */ too");



   myproc2();  // This is comment 



   /* This is comment too */ myproc3();



   myproc4();



   /* This is

      multiline comment */



   myproc5();



   // This is "cut-line"  \

and prolongation of single-line comment



   myproc6();



   printf(  " This is multiline \

string constant                 \

without /* comment. Don't /*  \

touch me. */ please" );



   /* This is multiline comment

      // this is single-line comment inside multiline */



   myproc7();



   /* This is multiline comment ...

       /* prolongation ....

       end of comment here -> */  



   myproc8();



   return 1;

}



Данные выходного файла "test.wc":

int myproc1()

{

   const char* nc = " Don't touch text /* inside */ quoted strings ";



   printf(" This is // not comment ");

   

   printf(" This is /* not comment */ too");



   myproc2();



   myproc3();



   myproc4();



   myproc5();



   myproc6();



   printf(  " This is multiline \

string constant                 \

without /* comment. Don't /*  \

touch me. */ please" );



   myproc7();



   myproc8();



   return 1;

}

