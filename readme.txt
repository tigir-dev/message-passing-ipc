Derleme:
gcc server.c -o server.o
gcc client.c -o client.o

Çalıştırma:
./server.o
./client.o

Program istemci tarafında rasgele oluşturulan 1000 elemanlı bir integer dizisini ve istemci pid değerini 3 farklı mesaj olarak gönderip
sunucu tarafında gelen diziyi sıralayarak mesaj olarak gelen istemci pid değeri adında bir dosya oluşturup bu dosyaya sıralanmış
diziyi yazmakta. Sunucu tarafından istemci tarafına sıralanmış diziyi gönderemiyor, bundan ötürü sadece sıralanmamış diziyi standart çıktıya
bastırıyor.