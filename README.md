
# ft_irc



1: https://glitter-muskox-81c.notion.site/KVIrc-IRC-Projesi-Client-a1c59174db354bb4900ac76a8d7435d2 <br>
2: https://modern.ircdocs.horse/ <br>


::: DİKKAT⚠️ Bu yazıda 42 ft_irc ve çoklu soket programlamanın server kısmına odaklanılmıştır. Eksik veya yanlış yazılmış bir şey görürseniz yazının altına ekleyeceğim iletişim kısmından ulaşın lütfen. :::

Yazının daha teknik kısımlarına inmeden önce kısaca birkaç temel kavramı hızlca hatırlayalım.

Server nedir?
Bilgisayar ağları ve iletişim sistemleri üzerinde önemli bir rol oynayan “server” (sunucu), istemcilere (clients) hizmet sağlayan, istemcilerden gelen talepleri işleyen ve bu taleplere cevap veren bir bilgisayar veya yazılım sistemidir. Server, genellikle bir ağ üzerindeki diğer cihazlara hizmet vermek üzere tasarlanmıştır.

Socket nedir?
Soket, bilgisayarlar arasında veri transferini sağlayan bir tür iletişim kanalıdır. İki bilgisayar arasında bir bağlantı noktası oluşturarak, bu noktadan veri gönderip alabilirsiniz. Her bilgisayarın bir IP adresi vardır ve soket, bu IP adresi üzerinden belirli bir port numarasına bağlanarak iletişim kurar.

IP adres nedir?
IP adresi (Internet Protocol Address), bir cihazın (bilgisayar, telefon, yazıcı, vs.) internet üzerindeki benzersiz tanımlayıcısıdır. IP adresleri, cihazların bir ağ üzerinde iletişim kurabilmesi için kullanılır. İki tür IP adresi bulunmaktadır: IPv4 (Internet Protocol version 4) ve IPv6 (Internet Protocol version 6).

Port nedir?
Port, bilgisayarlar arasında iletişim kurarken belirli türdeki trafiği yönlendirmek için kullanılan numaralardır. Her bir cihazın bir IP adresine ek olarak bir veya birden fazla porta sahip olabilir. Portlar, belirli bir uygulamaya veya hizmete erişim sağlar ve bu hizmetlerin tanımlı bir adresi gibi düşünülebilir.Port numaraları, 0 ile 65535 arasında bir değere sahip olabilir. Ancak, bu aralıktaki belirli numaralar genellikle belirli amaçlara hizmet eder. Örneğin, 0 ile 1023 arasındaki numaralar genellikle özel (well-known) portlar olarak adlandırılır ve belirli uygulamalara atanmıştır.

TCP nedir?
TCP (Transmission Control Protocol), internet üzerinde güvenilir veri iletimini sağlayan bir iletişim protokolüdür. Verileri sıralı ve hatasız bir şekilde iletir, bağlantı tabanlıdır, akış kontrolü sağlar ve hata kontrolü mekanizmalarına sahiptir. Web tarayıcıları, e-posta istemcileri, dosya transfer protokolleri gibi birçok uygulama, TCP’yi tercih eder.

UDP nedir?
UDP (User Datagram Protocol), hızlı ancak güvenilir olmayan bir iletişim protokolüdür. Veri gönderme ve almak için kullanılır, ancak veri bütünlüğü veya sıralama garantisi sağlamaz. Düşük gecikme ve basit bağlantısız iletim için tercih edilir. Özellikle ses, video akışı, oyunlar gibi uygulamalarda yaygın olarak kullanılır.

🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉

Eveeettt sıkıcı kısmı bitirdiğimize göre kod yazığımız ve server oluşturduğumuz eğlenceli kısma geçelim. Oluşturacağımız serverin sadece bir istemci(client) ile iletişime geçebileceğini birden fazla istemciyi kabul etmeyeceğini belirtelim. ft_irc projesinde oluşturacağınız sunucu(server) Birden fazla istemciyi destekleyebilmeli. Yazımızın sonunda birden fazla istemciyi destekleyecek serverin hangi yapıları ve nasıl olması grektiğinden de bahsedeceğiz. Hadi başlayalım!

Soket Server Oluşturma adımları
1. socket()
socket fonksiyonu, ağ programlamasında kullanılan soketleri oluşturmak için kullanılan bir sistem çağrısıdır

socket() fonksiyon prototipi!

#include <sys/types.h>
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
Argümanlar
domain: Soketin kullanılacağı iletişim domainini belirtir. Örneğin, AF_INET IPv4 adresleme kullanırken, AF_INET6 IPv6 adresleme kullanır.
type: Soket türünü belirtir. Örneğin, SOCK_STREAM TCP (güvenilir, bağlantı tabanlı) soketi, SOCK_DGRAM UDP (güvenilir olmayan, bağlantısız) soketi belirtir.
protocol: Soketin kullanılacağı protokolü belirtir. Genellikle 0 olarak belirtilir ve otomatik olarak uygun protokol atanır.
Dönüş değeri
Hata durumunda -1 döner. Başarı durumunda da oluşan socketin dosya tanımlayıcısını(fd) döner.

Şimdi kendi serverimizi oluşturmak için ilk kodumuzu yazalım ilerledikçe bu kodun üzerine eklemeler yapacağız.

//eddited by Talha demir
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
int main() 
{
		//socket fonksiyonunun dönüş değerini tutacak bir integer değişken tanımlıyoruz
		int server_socket;
		/*
			socket fonksiyonun domain argümanını AF_INET ile yani IPV4 ile başlatıyoruz
			
			hangi dosya transfer protokolünü seçeceğimiz ikinci argümanda TCP protokolünü temsil
			eden SOCK_STREAM değerini giriyoruz. Hız değilde güvenlik bizim için daha önemli
			olduğu için TCP seçtik.
		*/
	  server_socket = socket(AF_INET, SOCK_STREAM, 0);
		
		//burada soketin doğru bir şekilde oluşup oluşmadığını kontrol ediyoruz
    if (server_socket == -1) 
		{
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
		
		//program bittikten sonra açılan fd'yi kapatalım
    close(server_socket);
    return 0;
}
//eddited by Talha demir
2. sockaddr_in structı
sockaddr_in structu oluşacak soketin port ve adress bilgilerini oluşturmak için netinet/in.h

altında bulunan özel bir yapıdır. Burada sockaddr_in structunun üç özelliği ile ilgileneceğiz.

2.1 .sin_family
sin_family sockaddr_in structunun altında bulunan ve oluşturacağımız soketin hangi IP versiyonunun

kullanılacağını belirttiğimiz özelliktir.

sin_family prototip!

sockaddr_in server_address;
server_address.sin_family = AF_INET; // Ağ türünü IPv4 olarak ayarladık
2.2 .sin_port
sin_port, struct sockaddr_in yapısının bir üyesidir ve bir soketin kullanacağı port numarasını belirtir.

Genellikle, bu değer ağ baytlarına dönüştürülerek atanır. Çünkü ağ baytları, farklı bilgisayar mimarilerindeki farklı byte sıralamalarını ele almak için kullanılır. Bu dönüşüm işlemi için htons (host to network short) fonksiyonu kullanılır.

sin_port prototip!

sockaddr_in server_address;
server_address.sin_port = htons(6667); // Port numarasını 6667 olarak ayarladık
2.3 .sin_addr.s_addr
.sin_addr.s_addr özelliği sunucunun hangi IP adresi üzerinden gelen istemcileri dinleyeceğini belirten bir değer atar.

.sin_addr.s_addr prototip!

sockaddr_in server_address;
server_address.sin_addr.s_addr = inet_addr("192.168.1.1"); // Örneğin burada sunucu sadece 192.168.1.1 iPV+ adresi üzerinden gelen istemcileri kabul edecektir
sockaddr_in structu ve içinde barındırdığı değerleri anladığımıza göre hadi bunu serveri oluşturduğumuz koda uyarlayalım.

//eddited by Talha demir
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
int main() 
{
		//socket fonksiyonunun dönüş değerini tutacak bir integer değişken tanımlıyoruz
		int server_socket;
		/*
			socket fonksiyonun domain argümanını AF_INET ile yani IPV4 ile başlatıyoruz
			
			hangi dosya transfer protokolünü seçeceğimiz ikinci argümanda TCP protokolünü temsil
			eden SOCK_STREAM değerini giriyoruz. Hız değilde güvenlik bizim için daha önemli
			olduğu için TCP seçtik.
		*/
	  server_socket = socket(AF_INET, SOCK_STREAM, 0);
		
		//burada soketin doğru bir şekilde oluşup oluşmadığını kontrol ediyoruz
    if (server_socket == -1) 
		{
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
		
		//sockaddr_in türündeki structumuzu oluşturalım.
    sockaddr_in server_address;
		
		//burada hangi ağ türünü kullanacağımı belirliyoruz IPV4 seçtik.
    server_address.sin_family = AF_INET;
		//Burada port numaramızı belirliyoruz. 6667 portunu kullandık
    server_address.sin_port = htons(8080);
	
		//hangi IP adresleri üzerinden gelecek istemcileri kabul edeceğimizi belirliyoruz. 
		//INADDR_ANY diyerek herhangi bir IP üzerinden gelecek tüm istemcileri kabul edeceğimizi belirttik.
    server_address.sin_addr.s_addr = INADDR_ANY;
		//program bittikten sonra açılan fd'yi kapatalım
    close(server_socket);
    return 0;
}
//eddited by Talha demir
3. Bind
bind() fonksiyonu oluşturulan socket ile addresleri birbirine bağlayıp; socketin hangi porttan, hangi ip adresi üzerinden dinleme yapacağını belirlemeye yarayan bir sistem çağrısıdır.

bind prototip!

#include <sys/types.h>
#include <sys/socket.h>
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
Argümanlar
sockfd: bağlanacak soketin fd’si.
addr: oluşturulan sockaddr_in structu.
addrlen: oluşturulan sockaddr_in structu büyüklüğü.
Dönüş değeri
Hata durumunda -1 döner.

bind fonksiyonu ile soketin oluşturulan addrese bağlanmasını uygulayan kod!

//eddited by Talha demir
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
int main() 
{
		//socket fonksiyonunun dönüş değerini tutacak bir integer değişken tanımlıyoruz
		int server_socket;
		/*
			socket fonksiyonun domain argümanını AF_INET ile yani IPV4 ile başlatıyoruz
			
			hangi dosya transfer protokolünü seçeceğimiz ikinci argümanda TCP protokolünü temsil
			eden SOCK_STREAM değerini giriyoruz. Hız değilde güvenlik bizim için daha önemli
			olduğu için TCP seçtik.
		*/
	  server_socket = socket(AF_INET, SOCK_STREAM, 0);
		
		//burada soketin doğru bir şekilde oluşup oluşmadığını kontrol ediyoruz
    if (server_socket == -1) 
		{
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
		
		//sockaddr_in türündeki structumuzu oluşturalım.
    sockaddr_in server_address;
		
		//burada hangi ağ türünü kullanacağımı belirliyoruz IPV4 seçtik.
    server_address.sin_family = AF_INET;
		//Burada port numaramızı belirliyoruz. 6667 portunu kullandık
    server_address.sin_port = htons(8080);
	
		//hangi IP adresleri üzerinden gelecek istemcileri kabul edeceğimizi belirliyoruz. 
		//INADDR_ANY diyerek herhangi bir IP üzerinden gelecek tüm istemcileri kabul edeceğimizi belirttik.
    server_address.sin_addr.s_addr = INADDR_ANY;
		
		
		//dönüş değerini tutmak için integer değer tanımlaması yapalım.
		integer bind_val;
	
		//yukarıda fonksiyonun argümanlarını anlattığımız şekli ile yerine yazalım.
		bind_val = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
		//bağlantının doğru bir şekilde uygulandığına bakalım.
    if (bind_val)
    {
        std::cerr << "bind error\\n";
        exit(1);
    }
		//program bittikten sonra açılan fd'yi kapatalım.
    close(server_socket);
    return 0;
}
//eddited by Talha demir
4. Listen
Teknik sunucu soketini oluşturduk fakat herhangi bir işlevi yok. İstemciler üzerinden gelecek olan verileri alıp işleyebilmesi için dinleme moduna geçmesi gerekiyor dolayısıyla sunucuyu listen() fonksiyonu ile dinleme moduna alacağız.

listen prototip!

#include <sys/types.h>
#include <sys/socket.h>
int listen(int sockfd, int backlog);
Argümanlar
sockfd: dinlemeye geçecek soketin fd’si.ı (file descriptor).
backlog: Bağlantı sırasında bekleyen maksimum bağlantı sayısı.
Dönüş değeri
Hata durumunda -1 döner.

Kendi sunucumuzu oluşturduğumuz koddaki sunucuyu dinleme moduna alalım

//eddited by Talha demir
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
int main() 
{
		//socket fonksiyonunun dönüş değerini tutacak bir integer değişken tanımlıyoruz
		int server_socket;
		/*
			socket fonksiyonun domain argümanını AF_INET ile yani IPV4 ile başlatıyoruz
			
			hangi dosya transfer protokolünü seçeceğimiz ikinci argümanda TCP protokolünü temsil
			eden SOCK_STREAM değerini giriyoruz. Hız değilde güvenlik bizim için daha önemli
			olduğu için TCP seçtik.
		*/
	  server_socket = socket(AF_INET, SOCK_STREAM, 0);
		
		//burada soketin doğru bir şekilde oluşup oluşmadığını kontrol ediyoruz
    if (server_socket == -1) 
		{
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
		
		//sockaddr_in türündeki structumuzu oluşturalım.
    sockaddr_in server_address;
		
		//burada hangi ağ türünü kullanacağımı belirliyoruz IPV4 seçtik.
    server_address.sin_family = AF_INET;
		//Burada port numaramızı belirliyoruz. 6667 portunu kullandık
    server_address.sin_port = htons(8080);
	
		//hangi IP adresleri üzerinden gelecek istemcileri kabul edeceğimizi belirliyoruz. 
		//INADDR_ANY diyerek herhangi bir IP üzerinden gelecek tüm istemcileri kabul edeceğimizi belirttik.
    server_address.sin_addr.s_addr = INADDR_ANY;
		
		
		//dönüş değerini tutmak için integer değer tanımlaması yapalım.
		integer bind_val;
	
		//yukarıda fonksiyonun argümanlarını anlattığımız şekli ile yerine yazalım.
		bind_val = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
		//bağlantının doğru bir şekilde uygulandığına bakalım.
    if (bind_val)
    {
        std::cerr << "bind error\\n";
        exit(1);
    }
		//dönüş değerini tutmak için integer değer tanımlaması yapalım.
		int list_val;
		
		//sunucu aynı anda beş istemciden gelen isteği dinleyebilir
		list_val = listen(server_socket, 5);
		
		//doğru bir şekilde dinlemeye geçip geçmediğini kontrol edelim.
		if (list_val)
    {
        std::cerr << "list error\\n";
        exit(1);
    }
		
		//sunucunun dinlemeye geçtiğini göstermek için bir mesaj basalım.
		std::cout << "server is listening\\n"
		//program bittikten sonra açılan fd'yi kapatalım.
    close(server_socket);
    return 0;
}
//eddited by Talha demir
5. Accept
listen() fonksiyonu ile gelen bağlantıları dinlemeye başlayan sunucu accept() fonksiyonu ile bu bağlantıları kabul eder. Yazacağımız kod üzerinden nasıl yapıldğı daha iyi anlaşılacaktır.

accept prototip!

#include <sys/types.h>
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
Argümanlar
sockfd: dinlemeye geçen soketin fd’si.ı (file descriptor).
addr: Bağlantı kuran istemcinin adres bilgilerini içeren sockaddr yapısı.
addrlen: addr yapısının boyutunu belirten bir değer.
Dönüş değeri
Hata durumunda -1 döner.

Dinlemeye aldığımız serveri şimdi accept ile gelen bağlantıları kabul edecek yapıya getirelim

//eddited by Talha demir
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
int main() 
{
		//socket fonksiyonunun dönüş değerini tutacak bir integer değişken tanımlıyoruz
		int server_socket;
		/*
			socket fonksiyonun domain argümanını AF_INET ile yani IPV4 ile başlatıyoruz
			
			hangi dosya transfer protokolünü seçeceğimiz ikinci argümanda TCP protokolünü temsil
			eden SOCK_STREAM değerini giriyoruz. Hız değilde güvenlik bizim için daha önemli
			olduğu için TCP seçtik.
		*/
	  server_socket = socket(AF_INET, SOCK_STREAM, 0);
		
		//burada soketin doğru bir şekilde oluşup oluşmadığını kontrol ediyoruz
    if (server_socket == -1) 
		{
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
		
		//sockaddr_in türündeki structumuzu oluşturalım.
    sockaddr_in server_address;
		
		//burada hangi ağ türünü kullanacağımı belirliyoruz IPV4 seçtik.
    server_address.sin_family = AF_INET;
		//Burada port numaramızı belirliyoruz. 6667 portunu kullandık
    server_address.sin_port = htons(8080);
	
		//hangi IP adresleri üzerinden gelecek istemcileri kabul edeceğimizi belirliyoruz. 
		//INADDR_ANY diyerek herhangi bir IP üzerinden gelecek tüm istemcileri kabul edeceğimizi belirttik.
    server_address.sin_addr.s_addr = INADDR_ANY;
		
		
		//dönüş değerini tutmak için integer değer tanımlaması yapalım.
		integer bind_val;
	
		//yukarıda fonksiyonun argümanlarını anlattığımız şekli ile yerine yazalım.
		bind_val = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
		//bağlantının doğru bir şekilde uygulandığına bakalım.
    if (bind_val)
    {
        std::cerr << "bind error\\n";
        exit(1);
    }
		//dönüş değerini tutmak için integer değer tanımlaması yapalım.
		int list_val;
		
		//sunucu aynı anda beş istemciden gelen isteği dinleyebilir
		list_val = listen(server_socket, 5);
		
		//doğru bir şekilde dinlemeye geçip geçmediğini kontrol edelim.
		if (list_val)
    {
        std::cerr << "list error\\n";
        exit(1);
    }
		//sunucunun dinlemeye geçtiğini göstermek için bir mesaj basalım.
		std::cout << "server is listening\\n"
		//burada sonsuz bir döngü açtık çünkü sunucumuzun gelen verileri 
		//sürekli kabul edip işleyebilmesini istiyoruz.
		while(1)
    {
				//dönüş değerini tutmak için integer değer tanımlaması yapalım.
        int acc;
				//accept fonksiyonunun üçüncü argümanı için 
				//server_address yapısnın boyutunu socklen_t tipinde tutacak bir değişken tanımladık.
        socklen_t sock_len;
				
				sock_len = sizeof(sin);
				//gelen bağlantıları kabul edelim.
        acc = accept(sock,(struct sockaddr *)&sin, &sock_len);
				
				//doğru bir şekilde bağlanıp bağlanmadığına bakalım.
        if(acc < 0)
        {
            std::cerr << "accept error\\n";
            return 1;
        }
		}
		//program bittikten sonra açılan fd'yi kapatalım.
    close(server_socket);
    return 0;
}
//eddited by Talha demir
6. recv
recv fonksiyonu, soket programlamasında kullanılan bir sistem çağrısıdır ve bir soketten veri almak için kullanılır. Bu fonksiyon, send fonksiyonu tarafından gönderilen verileri almak için kullanılır.

recv prottip!

#include <sys/types.h>
#include <sys/socket.h>
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
Argümanlar
sockfd: Veri alınacak soketin dosya tanımlayıcısı (file descriptor).
buf: Alınacak verinin depolanacağı bellek bloğunun başlangıç adresi.
len: Alınacak verinin maksimum boyutu.
flags: İlave kontrol flag'leri.
Dönüş değeri

Hata durumunda -1 döner.

Oluşturduğumuz sunucuya bağlantılar üzerinden gelen mesajları yakalayacak recv fonksiyonunu uygulayalım!

//eddited by Talha demir
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
int main() 
{
		//socket fonksiyonunun dönüş değerini tutacak bir integer değişken tanımlıyoruz
		int server_socket;
		/*
			socket fonksiyonun domain argümanını AF_INET ile yani IPV4 ile başlatıyoruz
			
			hangi dosya transfer protokolünü seçeceğimiz ikinci argümanda TCP protokolünü temsil
			eden SOCK_STREAM değerini giriyoruz. Hız değilde güvenlik bizim için daha önemli
			olduğu için TCP seçtik.
		*/
	  server_socket = socket(AF_INET, SOCK_STREAM, 0);
		
		//burada soketin doğru bir şekilde oluşup oluşmadığını kontrol ediyoruz
    if (server_socket == -1) 
		{
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
		
		//sockaddr_in türündeki structumuzu oluşturalım.
    sockaddr_in server_address;
		
		//burada hangi ağ türünü kullanacağımı belirliyoruz IPV4 seçtik.
    server_address.sin_family = AF_INET;
		//Burada port numaramızı belirliyoruz. 6667 portunu kullandık
    server_address.sin_port = htons(8080);
	
		//hangi IP adresleri üzerinden gelecek istemcileri kabul edeceğimizi belirliyoruz. 
		//INADDR_ANY diyerek herhangi bir IP üzerinden gelecek tüm istemcileri kabul edeceğimizi belirttik.
    server_address.sin_addr.s_addr = INADDR_ANY;
		
		
		//dönüş değerini tutmak için integer değer tanımlaması yapalım.
		integer bind_val;
	
		//yukarıda fonksiyonun argümanlarını anlattığımız şekli ile yerine yazalım.
		bind_val = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
		//bağlantının doğru bir şekilde uygulandığına bakalım.
    if (bind_val)
    {
        std::cerr << "bind error\\n";
        exit(1);
    }
		//dönüş değerini tutmak için integer değer tanımlaması yapalım.
		int list_val;
		
		//sunucu aynı anda beş istemciden gelen isteği dinleyebilir
		list_val = listen(server_socket, 5);
		
		//doğru bir şekilde dinlemeye geçip geçmediğini kontrol edelim.
		if (list_val)
    {
        std::cerr << "list error\\n";
        exit(1);
    }
		//sunucunun dinlemeye geçtiğini göstermek için bir mesaj basalım.
		std::cout << "server is listening\\n"
		//burada sonsuz bir döngü açtık çünkü sunucumuzun gelen verileri 
		//sürekli kabul edip işleyebilmesini istiyoruz.
		while(1)
    {
				//dönüş değerini tutmak için integer değer tanımlaması yapalım.
        int acc;
				//accept fonksiyonunun üçüncü argümanı için 
				//server_address yapısnın boyutunu socklen_t tipinde tutacak bir değişken tanımladık.
        socklen_t sock_len;
				
				sock_len = sizeof(sin);
				//gelen bağlantıları kabul edelim.
        acc = accept(sock,(struct sockaddr *)&sin, &sock_len);
				
				//doğru bir şekilde bağlanıp bağlanmadığına bakalım.
        if(acc < 0)
        {
            std::cerr << "accept error\\n";
            return 1;
        }
				
				//recv fonksiyonuna gelecek mesajların tutulduğu char dizisi.
				char buff[1024];
				//dönüş değerini tutmak için integer değer tanımlaması yapalım.
				int rec_val;
				
				//bağlantısı kabul edilen istemciden gelen mesajı buff içine atalım
        rec_val = recv(acc, buff, sizeof(buff), 0)
				
				//mesaj doğru bir şekilde alndıysa basalım.
				if(rec_val != -1)
            std::cout << "client message: "<< buff <<std::endl;
		}
		//program bittikten sonra açılan fd'yi kapatalım.
    close(server_socket);
    return 0;
}
//eddited by Talha demir
Şimdiye kadar soket programlama tekniklerini kullanarak basit bir sunucu oluşturduk. Yazının başında belirttiğimiz gibi bu sunucu tek istemci üzerinden gelen bağlantıları kabul eder. Birden fazla istemciyi kabul etmesi için select, poll gibi çoklu socket takibi yapan yapıları kullanmanız gerekiyor.

Select
select fonksiyonu ile ilgili yazdığım yazıya aşağdaki linkten ulaşabilirsiniz.

https://medium.com/@demirtalha093/select-5263a271f740

Çoklu istemciyi destekleyen bir server örneği

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
class ClientInfo {
public:
    int socket_fd;
    sockaddr_in address;
    ClientInfo(int fd, sockaddr_in addr) : socket_fd(fd), address(addr) {}
};
class Server {
public:
    int _socket;
    struct sockaddr_in _sin;
    int _bin;
    int _lis;
    int _port;
    Server(char *str);
    void serving();
};
Server::Server(char *str) {
    _socket = -1;
    _bin = -1;
    _lis = -1;
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    _port = atoi(str);
    if (_socket < 0) {
        std::cerr << "sock error\\n";
        exit(1);
    }
    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(_port);
    _sin.sin_addr.s_addr = INADDR_ANY;
    _bin = bind(_socket, (struct sockaddr *)&_sin, sizeof(_sin));
    if (_bin) {
        std::cerr << "bind error\\n";
        exit(1);
    }
    _lis = listen(_socket, 5);
    if (_lis) {
        std::cerr << "list error\\n";
        exit(1);
    }
    std::cout << "server is listening\\n";
}
void Server::serving() {
    fd_set rfds, tmp_rfds;
    int max_sd, new_socket;
    struct sockaddr_in client;
    socklen_t addr_len = sizeof(client);
    std::vector<ClientInfo> clients;
    FD_ZERO(&rfds);
    FD_SET(_socket, &rfds);
    max_sd = _socket;
    std::cout << "Server is waiting for connections on port " << _port << std::endl;
    while (true) {
        tmp_rfds = rfds;
        if (select(max_sd + 1, &tmp_rfds, NULL, NULL, NULL) == -1) {
            std::cerr << "select error\\n";
            break;
        }
        if (FD_ISSET(_socket, &tmp_rfds)) {
            if ((new_socket = accept(_socket, (struct sockaddr *)&client, &addr_len)) == -1) {
                std::cerr << "accept error\\n";
                break;
            } else {
                std::cout << "New connection from " << inet_ntoa(client.sin_addr) << " on socket " << new_socket << std::endl;
                clients.push_back(ClientInfo(new_socket, client));
                FD_SET(new_socket, &rfds);
                if (new_socket > max_sd)
                    max_sd = new_socket;
            }
        }
        for (std::vector<ClientInfo>::iterator it = clients.begin(); it != clients.end();) {
            int client_socket = it->socket_fd;
            if (FD_ISSET(client_socket, &tmp_rfds)) {
                char buffer[1024];
                int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
                if (bytes_received <= 0) {
                    std::cout << "Client on socket " << client_socket << " disconnected." << std::endl;
                    close(client_socket);
                    FD_CLR(client_socket, &rfds);
                    it = clients.erase(it);  // Iterator'ı güncelle
                } else {
                    buffer[bytes_received] = '\\0';
                    std::cout << "Received from client " << client_socket << ": " << buffer << std::endl;
                    ++it;
                }
            } else {
                ++it;
            }
        }
    }
    close(_socket);
}
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }
    Server server(argv[1]);
    server.serving();
    return 0;
}


# select()

::: DİKKAT⚠️
Bu yazıda select() sistem çağrısının 42 FT_IRC  projesi ve çoklu soket programlama kullanımı üzerine odaklanılmıştır. Eksik veya yanlış yazılmış bir şey görürseniz yazının altına ekleyeceğim iletişim kısmından ulaşın lütfen.
:::

**`select`**, UNIX ve POSIX işletim sistemlerinde bulunan bir sistem çağrısıdır ve çoklu giriş/çıkış işlemlerini takip etmek için kullanılır. Temel olarak, bir grup dosya tanımlayıcısını (file descriptor) izler ve bu dosya tanımlayıcıları üzerindeki olayları belirler.

https://man7.org/linux/man-pages/man2/select.2.html

## PROTOTİP

```c
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
```

# Argumanlar

1. **`nfds`**:
    - İzlenecek dosya tanımlayıcılarının en büyük değisinin bir üstüdür (en büyük dosya tanımlayıcısı + 1).
    - **`nfds`**, **`select`** fonksiyonuna geçilen diğer dosya tanımlayıcılarının içinde en büyük değeri temsil etmelidir.
2. **`readfds`**:
    - Okuma (read) olaylarını takip etmek istediğiniz dosya tanımlayıcılarının kümesidir.
    - **`FD_SET(fd, readfds)`** fonksiyonuyla dosya tanımlayıcısını kümeye ekleyebilirsiniz.
3. **`writefds`**:
    - Yazma (write) olaylarını takip etmek istediğiniz dosya tanımlayıcılarının kümesidir.
    - **`FD_SET(fd, writefds)`** fonksiyonuyla dosya tanımlayıcısını kümeye ekleyebilirsiniz.
4. **`exceptfds`**:
    - İstisnai durumları (exceptional conditions) takip etmek istediğiniz dosya tanımlayıcılarının kümesidir.
    - Genellikle **`NULL`** olarak geçilir, yani istisnai durumları izlemek istemiyorsanız bu parametreyi kullanmazsınız.
5. **`timeout`**:
    - **`select`** fonksiyonunun bekleyeceği maksimum zamanı belirler.
    - **`struct timeval`** türünde bir zaman yapısıdır. Eğer bu parametre **`NULL`** ise, **`select`** fonksiyonu olaylar gerçekleşene kadar bekler.
    - Eğer bu parametre **`0`** ise, fonksiyon hiç bekleme yapmadan hemen kontrolü geri verir.
    - Aksi takdirde, belirtilen zaman dilimi içinde olaylar gerçekleşmezse, fonksiyon kontrolü geri verir.

## return degeri

```c
int result = select(max_sd + 1, &read_fds, NULL, NULL, NULL);

if (result == -1) {
    perror("select"); // Hata durumu
} else if (result > 0) {
    // Olaylar gerçekleşti, result değeri gerçekleşen olay sayısını temsil eder
} else {
    // Zaman aşımı durumu veya başka bir durum
}
```

 Bu örnekte, **`select`** fonksiyonunun dönüş değeri olan **`result`** değeri, gerçekleşen olay sayısını ifade eder. Eğer **`result`** değeri **`-1`** ise, bir hata meydana gelmiş ve **`perror`** fonksiyonu kullanılarak hatanın ayrıntıları ekrana yazdırılmıştır. Eğer **`result`** değeri **`0`** ise, belirtilen zaman dilimi içinde olay gerçekleşmemiş demektir. Aksi takdirde, **`result`** değeri, gerçekleşen olay sayısını gösterir ve ilgili işlemler gerçekleştirilebilir.

# select için argümanların oluşma süreci

## fd_set

```c
fd_set master_set, working_set;

```

 Bu kod parçacığında ft_set tipinde iki değişken oluşturduk. neden iki tane oluşturduğumuzu daha sonra konuşacağız. 

 **`fd_set`**  türü ne işe yarıyor ? **`fd_set`** türü, **`select`**fonksiyonu ile birlikte kullanılan bir dosya tanımlayıcı (file descriptor) kümesi (set) türüdür. örneğin elinizde üç adet soket bulunsun fd_set  içinde bu soketleri numaraları ile beraber tutar.

## FD_ZERO

**`FD_ZERO`** fonksiyonu, bir **`fd_set`** türündeki küme (set) verisini sıfırlamak için kullanılır. Bu fonksiyon, **`fd_set`** türündeki bir nesnenin tüm elemanlarını temizler, yani küme içindeki tüm dosya tanımlayıcılarını kaldırır.

```c
FD_ZERO(&master_set)
```

Yukarıdaki kod paraçacığını master_set içindeki socketlerden temizledik. Bu işlem güvenli kodalma için fd_set tipinde oluşturulan değişkenden sonra uygulanaması tavsiye deilir ya da içini boşaltmak istediğiniz soket kümesi(fd_set türündeki değişken) üzerine de uygulayabilirsiniz.

## FD_SET

```c
FD_SET(socket1, &master_set);
```

FD_SET oluşan soketin fd_set tipindeki soket kümesinin içine atılmasını sağlar. Örnek vermek gerekirse içinde (6, 8, 5) socket fd bulunduran bir soket kümesi olduğunu düşünelim. sonrasında 9 fd numaralı bir soketi soket kümesi içine atarsak yeni soket kümesi (6, 8, 5) olur

Şana kadar yeptığımız işlemleri bir kod üzerinden özetleyelim.

```c
//eddited by Talha demir
//fd_set türünde bir soket kümesi oluşturduk. 
fd_set my_set;

//soket kümeainin içini temizledik
FD_ZERO(&my_set);

//my_set kumesi: {}

// Başlangıç kümesine (6, 8, 5) dosya tanımlayıcılarını(fd'leri) ekleyelim
FD_SET(6, &my_set);
FD_SET(8, &my_set);
FD_SET(5, &my_set)

//my_set kumesi: {6 8 5}

// Yeni bir dosya tanımlayıcısını (7) kümeye ekleyelim
FD_SET(7, &my_set);
//my_set kumesi: {6 8 5 7}
```

*Yukarıda yazdığımız kod parçacığının bir örnek olduğunu unutmayalım. Bundan sonraki süreçler ile bir bağlantısı yoktur.* 

## ne öğrendik

- [ ]  fd_set türü
- [ ]  FD_ZERO
- [ ]  FD_SET

---

## max_sd

```c
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
```

hatırlıyorsanız yazımızın başında şöyle bir kod parçacığı yazdık. şimdi giderek bu kod parçacağının görevine ve içindeki argümanlara nasıl ulaştığımızı öğrenmeye daha fazla yaklaşıyoruz.

ilk argümanımız olan nfds’den bahsedelim biraz. 

int nfds : fd_set türü ile oluşturduğumuz soket kümesi içinde bulunan soketlerin en büyük fd değerine sahip soketin fd numarasının bir fazlasını arguman olarak alır.

### Örnek

```c
//eddited by Talha demir
//fd_set türünde bir soket kümesi oluşturduk. 
fd_set my_set;

//soket kümeainin içini temizledik
FD_ZERO(&my_set);

//my_set kumesi: {}

// Başlangıç kümesine (6, 8, 5) dosya tanımlayıcılarını(fd'leri) ekleyelim
FD_SET(6, &my_set);
FD_SET(8, &my_set);
FD_SET(5, &my_set)

//my_set kumesi: {6 8 5}

// Yeni bir dosya tanımlayıcısını (7) kümeye ekleyelim
FD_SET(7, &my_set);
//my_set kumesi: {6 8 5 7}
```

*Yukarıda yazdığımız kod parçacığının bir örnek olduğunu unutmayalım. Bundan sonraki süreçler ile bir bağlantısı yoktur.* 

Burada `my_set` soket kümesinin içindeki en büyük fd değeri 8 fd numaralı sokettir.

Dolayısıyla bu kümenin içindeki en büyük değeri `int max_sd` isimli bir integerin içinde tutarsak. **max_sd = 8** olacaktır.

Soket kümemizin içindeki en büyük fd bulunduğuna göre bunun bir fazlasını alıp select fonksiyonunun ilk argümanı olarak atayabiliriz.

```c
//eddited by Talha demir
//fd_set türünde bir soket kümesi oluşturduk. 
fd_set my_set;

//soket kümeainin içini temizledik
FD_ZERO(&my_set);

//my_set kumesi: {}

// Başlangıç kümesine (6, 8, 5) dosya tanımlayıcılarını(fd'leri) ekleyelim
FD_SET(6, &my_set);
FD_SET(8, &my_set);
FD_SET(5, &my_set)

//my_set kumesi: {6 8 5}

// Yeni bir dosya tanımlayıcısını (7) kümeye ekleyelim
FD_SET(7, &my_set);
//my_set kumesi: {6 8 5 7}

//oluşturduğumuz soket kümesinin en büyük fd değerini max_sd içine attık
int max_sd;
max_sd = 8;

//bir fazlasını alıp nfds olarak düzenledik.
int nfds;
nfds = max_sd + 1;

select(nsfd,...);
```

*Yukarıda yazdığımız kod parçacığının bir örnek olduğunu unutmayalım. Bundan sonraki süreçler ile bir bağlantısı yoktur.* 

ÖNEMLİ!! 

max_sd + 1 yapmamızın sebebi select 0’dan nsfds-1’e kadar açılan tüm soketlerin üzerinde dolaşır. 1 eklediğimiz için select açılan tüm soketlerin üzerinde dolaşabilir duruma gelir. Neden en büyük fd numarasını aldığımızı da anlamış olduk. 

### select soketleri neden/nasıl izler

```c
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
```

tekrar prototipimize dönersek ilk argümanı tartıştık şimdi sıra ikinci argümanda.

ilk argümana `selectin izleyeceği soket kümesinin` en büyük fd değerinin bir fazlası demiştik.

peki hangi soketler? 

İkinci argüman olan **`readfds`** (okuma dosya tanımlayıcıları kümesi), **`select`** fonksiyonuna hangi dosya tanımlayıcılarının okuma olaylarını bekleyeceğini bildirir. Bu kümede bulunan dosya tanımlayıcıları, bu soketler üzerinden okuma işlemine hazır hale gelirse, **`select`** fonksiyonu uyandırılır.

Bu dosya tanımlayıcıları, genellikle soketler, dosya açıklıkları veya diğer giriş/çıkış kaynakları olabilir. Örneğin, bir sunucu uygulamasında, müşteri soketleri bu kümede yer alabilir. Okuma olayı, bu soketlere gelen veri olup olmadığını kontrol etmek için kullanılı

Şimdi ikinci argümanı ekleyerek kod parçacığımızı güncelleyelim!

```c
//eddited by Talha demir
//fd_set türünde bir soket kümesi oluşturduk. 
fd_set my_set;

//soket kümeainin içini temizledik
FD_ZERO(&my_set);

//my_set kumesi: {}

// Başlangıç kümesine (6, 8, 5) dosya tanımlayıcılarını(fd'leri) ekleyelim
FD_SET(6, &my_set);
FD_SET(8, &my_set);
FD_SET(5, &my_set);

//my_set kumesi: {6 8 5}

// Yeni bir dosya tanımlayıcısını (7) kümeye ekleyelim
FD_SET(7, &my_set);
//my_set kumesi: {6 8 5 7}

//oluşturduğumuz soket kümesinin en büyük fd değerini max_sd içine attık
int max_sd;
max_sd = 8;

//bir fazlasını alıp nfds olarak düzenledik.
int nfds;
nfds = max_sd + 1;

//select'in temel soket kümemizi bozmasını istemediğimizden bir kopyasını almalıyız.
fd_Set tmp_set;
tmp_set = my_set;
  
//şimdi kopyayı selecte gönderelim 
select(nsfd, tmp_set, ...);

```

*Yukarıda yazdığımız kod parçacığının bir örnek olduğunu unutmayalım. Bundan sonraki süreçler ile bir bağlantısı yoktur.* 

## 3-4- 5.  Argümanlar

FT_IRC projesinde sadece okuma dosya tanımlayıcıları  üzerine çalışacağımız için select fonksiyonunun diğer argümanları üzerine detaylı bir anlatım yapmayacağız ama yine de select fonksiyonunun daha iyi anlaşılması için kısaca bu argümanlardan da bahsedeceğiz.

1. **`writefds` (yazma dosya tanımlayıcıları kümesi):**
    - Bu parametre, **`select`** fonksiyonuna hangi dosya tanımlayıcılarının yazma olaylarını bekleyeceğini bildirir.
    - Eğer bu küme içindeki bir dosya tanımlayıcısı üzerinden yazma işlemi mümkün hale gelirse, **`select`** fonksiyonu uyandırılır.
    - Bu küme, genellikle bir soketin yazma olayını kontrol etmek veya bir dosyaya yazma işlemini izlemek için kullanılır.
2. **`exceptfds` (istisna dosya tanımlayıcıları kümesi):**
    - Bu parametre, **`select`** fonksiyonuna hangi dosya tanımlayıcılarının istisna olaylarını bekleyeceğini bildirir.
    - Eğer bu küme içindeki bir dosya tanımlayıcısı üzerinde bir istisna durumu meydana gelirse, **`select`** fonksiyonu uyandırılır.
    - İstisna durumları genellikle hata durumları veya olağan dışı durumları ifade eder. Örneğin, bir soketin bağlantısının koptuğu durum gibi.
3. **`timeout` (maksimum bekleme süresi):**
    - Bu parametre, **`select`** fonksiyonunun en fazla ne kadar süre boyunca bekleyeceğini belirler.
    - **`timeout`** argümanı, **`struct timeval`** türünde bir yapıdır ve iki alan içerir: **`tv_sec`** (saniye) ve **`tv_usec`** (mikrosaniye).
    - Eğer bu argüman **`NULL`** olarak atanırsa, **`select`** fonksiyonu olay meydana gelene kadar bekler.
    - Eğer **`0`** olarak atanırsa, fonksiyon anında kontrol sonuçlarını alır (bloklanmaz).
    - Belirli bir zaman aralığı belirlenmişse, fonksiyon olay meydana gelene kadar veya belirtilen zaman aralığı sona erene kadar bekler.

Kod parçacığımız ne durumda? hadi bakalım!

```c
//eddited by Talha demir
//fd_set türünde bir soket kümesi oluşturduk. 
fd_set my_set;

//soket kümeainin içini temizledik
FD_ZERO(&my_set);

//my_set kumesi: {}

// Başlangıç kümesine (6, 8, 5) dosya tanımlayıcılarını(fd'leri) ekleyelim
FD_SET(6, &my_set);
FD_SET(8, &my_set);
FD_SET(5, &my_set);

//my_set kumesi: {6 8 5}

// Yeni bir dosya tanımlayıcısını (7) kümeye ekleyelim
FD_SET(7, &my_set);
//my_set kumesi: {6 8 5 7}

//oluşturduğumuz soket kümesinin en büyük fd değerini max_sd içine attık
int max_sd;
max_sd = 8;

//bir fazlasını alıp nfds olarak düzenledik.
int nfds;
nfds = max_sd + 1;

//select'in temel soket kümemizi bozmasını istemediğimizden bir kopyasını almalıyız.
fd_Set tmp_set;
tmp_set = my_set;
  
//Kullanmadığımız argümanlara NULL atayark bypass ettik
//dönüş değeri -1 ise kod devam etmeyecektir.
if (select(nfds, &tmp_set, NULL, NULL, NULL) == -1)
{
            perror("select");
            exit();
}
```

*Yukarıda yazdığımız kod parçacığının bir örnek olduğunu unutmayalım. Bundan sonraki süreçler ile bir bağlantısı yoktur.*

## FD__ISSET

select ile çoklu soket programlamanın son konsepti olan FD_ISET makrosunu ele alalım

**`FD_ISSET`** makrosu, belirtilen **`fd`**'nin **`set`** kümesinde bulunup bulunmadığını kontrol eder. Eğer **`fd`** kümede bulunuyorsa ve belirli bir olaya hazır durumdaysa, **`FD_ISSET`** **`true`** değerini döndürür; aksi takdirde, **`false`** döndürür.

Bunu kod parçacığımız üzerinden gösterirsek daha iyi anlaşılır.

```c
//eddited by Talha demir
//fd_set türünde bir soket kümesi oluşturduk. 
fd_set my_set;

//soket kümeainin içini temizledik
FD_ZERO(&my_set);

//my_set kumesi: {}

// Başlangıç kümesine (6, 8, 5) dosya tanımlayıcılarını(fd'leri) ekleyelim
FD_SET(6, &my_set);
FD_SET(8, &my_set);
FD_SET(5, &my_set);

//my_set kumesi: {6 8 5}

// Yeni bir dosya tanımlayıcısını (7) kümeye ekleyelim
FD_SET(7, &my_set);
//my_set kumesi: {6 8 5 7}

//oluşturduğumuz soket kümesinin en büyük fd değerini max_sd içine attık
int max_sd;
max_sd = 8;

//bir fazlasını alıp nfds olarak düzenledik.
int nfds;
nfds = max_sd + 1;

//select'in temel soket kümemizi bozmasını istemediğimizden bir kopyasını almalıyız.
fd_Set tmp_set;
tmp_set = my_set;
  
//Kullanmadığımız argümanlara NULL atayark bypass ettik
//dönüş değeri -1 ise kod devam etmeyecektir.
if (select(nfds, &tmp_set, NULL, NULL, NULL) == -1)
{
            perror("select");
            exit();
}

//FD_ISSET makrosunun döneceği integer değeri bir integerde tutalım
int is_set;

is_set = FD_ISSET(9, &my_set)
if(is_set == 1)
{
		// soket üzerinde okuma olayı gerçekleşebilir hale geldi
    // İlgili işlemleri yapın
}

else if(is_set == 0)
{
	//soket kümemizin içinde bu sokete ulaşılmadı
	//soketi oluşturmak için ilgili işlemleri yapın
	FD_SET(9, &my_set);
}
```

*Yukarıda yazdığımız kod parçacığının bir örnek olduğunu unutmayalım. Bundan sonraki süreçler ile bir bağlantısı yoktur.*

Bu yazıda select fonksiyonunun işleyişi ve genel çalışma mantığı üzerine tartıştık. Umarım yardımcı olabilmişimdir. İyi çalışmalar herkese. 

# İLETİŞİM

linkedin: https://www.linkedin.com/in/talhadmr/

E-posta: demirtalha093@gmail.com
