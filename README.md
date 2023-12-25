# ft_irc

Şuan projenin kaynak taraması aşamasındayız. Bulduğunuz kaynakları buraya atabilirsiniz.

1: https://glitter-muskox-81c.notion.site/KVIrc-IRC-Projesi-Client-a1c59174db354bb4900ac76a8d7435d2 <br>
2: https://modern.ircdocs.horse/ <br>


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
