Akylly Öý Ulgamy

Referat
Mazmuny
    1. Arduino
    2. Raspberry Pi
      a) LAMP web serwer
	      b) Flask web serwer
    I. Web kamera		
    II. Suw we gaz mukdaryny hasaplamak
    III. Bag suwaryş ulgamy
	      c) Internete baglamak
	      d) Tok çeşmesi
       3.   Android app
        4.   Akylly otagyň funksiýalary

	1. Otagyň elektrik bilen işleýän ähli enjamlaryny Arduino mikrokontrolleri dolandyrýar. Oňa otagyň çyralary, penjireleri, perdeleri, dürtgüçleri(rozetka), we esasy ulgamlary (howa sazlaýjy ulgamy, suw we gaz syzmalar ulgamy, bag suwaryş ulgamy, biometriki howpsuzlyk ulgamy, audio ulgamy) degişlidir. Jemi 8 sany Arduino Uno mikrokontrolleri ulanyldy we olaryň her biri otagyň kesgitli we aýratyn bölegini (enjamlaryny) dolandyrýar. Mikrokontrollerleriň her birine etmeli işine görä, programma üpjünçiligi ýazyldy (C we C++ dilinde), ýöne muňa garamazdan, olar özara berk baglanyşyklydyr. Olar Master-Slave tertibinde bir-biri bilen sim arkaly birikdirildi. Master-Slave tertibi bolanda, esasy diýlip diňe bir mikrokontroller saýlanylýar. Ilki bilen ähli gelýän maglumatlary özi kabul edýär, seljerýär we kesgitli mikrokontrollere şol maglumaty iberýär. Bu bolsa esasy mikrokontrolleriň beýleki 7 sany mikrokontrolleriň her birine aýratynlykda ýa-da bilelikde maglumaty iberip bilýänligidir. Bu tertip mikrokontrolleriň ýalňyşmazlygynyň, gyzmazlygynyň öňüni alýar. Olaryň durnukly işlemegi üçin, her birine aýratynlykda 5V tok çeşmesi berildi we daşky sredanyň täsirinden gorar ýaly, olary tok ölçeyji enjam üçin niýetlenen gaba salyndy.

	2. Esasy mikrokontrollere gelýän maglumatlary, Raspberry Pi 4 minikompýuter ugradýar. Bu bir plataly minikompýuter NOOBS operasion ulgamda işleýär, onuň RAM 4GB deň bolup, ol birnäçe we agyr programma üpjünçiligini işletmäge ukyply. Minikompýuteriň içki ýady SD-CARD bolup, ýüklenilýän ähli programma üpjünçiligi, bukjalar, hatda operasion ulgamy hem şonda saklanylýar. Häzirki wagtda onuň ýady 16 GB deňdir we ony isledigiňçe ýokarlandyryp bolar. Ol 5V we minimum 3A tok çeşmesini talap edýär. Eger-de tok güýji pes bolup, köp işleri ýerine ýetirse onuň birden öçmegi mümkin. Beýleki minikompýuterlere garanyňda, onuň prosessory çalt gyzýar. Ony aşa gyzmakdan hem-de daşky sredadan gorar ýaly 3D printerde gap (daş) ýasaldy we gabyň içine kiçi ýelpewaç (kuler) goýuldy. 5V ýelpewaç göni minikompýuteriň GPIO -den iýmitlenýär.

 	a) Bu minikompýuteriň ulanylmagynyň esasy sebäpleriniň biri, onda simsiz aragatnaşygyny (Wi-Fi, Bluetooth) ýola goýup bolýar. Onuň kömegi bilen minikompýuter daşyndan gelýän maglumatlary simsiz we aralykdan kabul edip bilýär. Diýmek, islendik akylly telefon, planşet ýa-da kompýuter simsiz aragatnaşyk arkaly maglumaty iberip bilýär. Ýöne onuň üçin minikompýuteri web serwere öwürmek hökmanydyr. Web serwer ulanyjynyň ugradýan maglumatyny alyp we oňa görä jogap berýär. Bu ýerde 2 sany LAMP (Linux,Apache,MySQL,PHP) we Flask web serwerleri ýüklenildi. Olaryň her biri bir wagtda aýratyn programma üpjünçiligini işe girizýär. Daşyndan gelýän maglumatlary esasy kabul ediji bolup, LAMP web serweri hyzmat edýär. Maglumaty almak üçin PHP dilinde programma ýazyldy we şol web serweriň içine (var/www/html bukja) ýüklenildi.

Programmanyň maglumat alyş-çalşygy JSON formatda amala aşyrylýar. Bu tekstli format programma tarapyndan ýeňil we çalt okalýar. Ýokarda bellenilişi ýaly, akylly telefon, planşet, kompýuter maglumat iberiji bolup durýar. Programmanyň esasy maksady, gelen maglumatlary dessine Arduino mikrokontrollere ugratmak bolup durýar. Ýöne mikrokontrolleri Raspberry Pi 4 minikompýutere birikdirmek gerek. Arduino mikrokontrolleriň öz USB kabelini alyp, bir ujuny özüne, beýleki tarapyny bolsa Raspberry Pi 4 minikompýuteriň USB portuna birikdirmeli. Şeýle tertipde edilende maglumatlar ýitgisiz we çalt ugradylýar. Ýene bir bellemeli zat, programmanyň başynda ýaňy birikdirilen mikrokontrolleriň ady ýazylýar (/dev/tty/ACM0). Birnäçe gezek yzly-yzyna birikdirilende onuň ady üýtgäp biler. Şonuň üçin, minikompýutere Arduino IDE programma üpjünçiligini ýüklemeli we onuň sag tarapynyň aşaky burçunda mikrokontrolleriň ady görkeziler.

	b) Flask web serweri wideogözegçilik, ulanylan suwuň we gazyň mukdaryny hasaplamak, aşhana enjamlaryny (peç, howa çekiji) dolandyrmak we bag suwaryş ulgamyny öz içine alýar. 
	
	I.   Wideogözegçilik üçin 1 sany USB web kamera we 2 sany kiçi servo motor ulanyldy. Servo motorlar bilelikde, kamerany ýokary-aşak we çepe-saga öwrer ýaly edilip düzüldi. Ykjam görnüşe geler ýaly 3D printerde gap (daş) ýasaldy we tutuş ulgamy otagyň ....... burçunda goýuldy. 180° -ly servo motorlar kamerany 55° ýokary-aşak, 45° çepe-saga öwürýär we şeýlelikde otagyň içini doly synlamak bolar. Kameranyň USB kabelini minikompýuteriň USB portuna we şol sanda servo motorlaryň signalyny mikrokontrollere birikdirildi. Kamera üçin, Python dilinde programma üpjünçiligi ýazyldy, we minikompýuteriň iş stolunda saklanylýar. 

Programmany işe girizmek üçin minikompýuteriň terminalyny açyp,  "python /Desktop/camera/camera.py" şu buýrugy (komanda) ýazyp, enter düwmesine basmaly.
	
	II.   Aýyň dowamynda ulanylan suwuň we gazyň mukdaryny hasaplamak üçin, ýörite suw we gaz ölçeýji sensorlary ulanyldy. Suw ölçeýji sensory öýe gelýän suw turbasynyň, gaz ölçeýji sensory bolsa, öýe gelýän gaz turbasynyň aralygyna goýuldy. Bu sensorlaryň kömegi bilen, programma üpjünçiligi her gündäki ulanylan suwuň, gazyň mukdaryny we tölegini hasaplap, aýlyk netijäni çykarýar. Aýlyk netijede sarp edilen suwuň, gazyň mukdaryny we tölegini akylly telefondan, kompýuterden diagramma görnüşinde görmek bolýar. Mundan başga-da sarp edilen suw we gaz tölegini bank kartlary bilen töläp bolýar. Onuň üçin, öýden çykmak zerurlygy ýok. Hemme hasaplaşyk otagda gurnalan RFID modulyň kömegi bilen geçirilýär. Bu tutuş ulgamyň ululygy adaty akylly telefondan sähelçe uludyr we ony otagyň islendik ýerinde gurnap bolar. Bu ulgam hem şol programma üpjünçiliginiň esasynda işleýär. Tölegi amala aşyrmak üçin, bank kartyny RFID modulyň golaýyna eltmek ýeterlikdir. Elektrik bilen işleýän aşhana enjamlaryny (peç, howa çekiji) hem dolandyrmak mümkin. Howa çekijini we pejiň bar bolan 2 sany ojagyny (göz) aralykdan we wagta görä aýratynlykda dolandyryp bolýar. Haçanda peç ýakylanda ýa-da gaz syzmasy duýlanda howa çekiji awtomatiki ýagdaýda işläp başlaýar. Işläp duran pejiň ýa-da howa çekijiniň awtomatiki öçmegi üçin wagt (timer) goýup bolýar (10,30,60 minut aralygy). Wagtyň gutarmagy bilen olar awtomatiki ýagdaýda öçýär. Aşhana otagyndaky suw akydyjy hem awtomatlaşdyryldy. Onuň üçin, suw nasosy, 1 sany suw bekediji klapany we obýekt duýujy sensor ulanyldy. Haçanda eliňi suw akydyjynyň aşagyna elteniňde suw akmaga başlaýar. Bu proses 3 tapgyrda (tertip) işleýär: ilki bilen sensor obýekti duýýar, suw nasosy işleýär, soň bolsa suwuň bekediji klapany açylýar. Eliňi aýyran badyňa suwuň bekediji klapany ýapylýar, suw nasosy öçýär, we suw akmagyny bes edýär. Sensory suw akydyjynyň suw çykýan nokadynyň gapdalynda goýlup aşak tarap gönükdirildi. Pejiň, howa çekijiniň, suw bekediji klapanyň, suw nasosynyň işlemegine Arduino mikrokontrolleri, programma üpjünçiligine bolsa, Raspberry Pi 4 minikompýuter jogap berýär.
	
	III.   Mellekde we ş.m. öýüň golaýyndaky ýerlerde baglary wagtly-wagtyna suwarmak işleri awtomatiki ýagdaýa getirmek üçin, bag suwaryş ulgamy işlenilip düzüldi. Onuň üçin, [toprak] sensory, suw nasosy, suw turbalary ulanyldy. [Toprak] sensory çyglylygy we olaryň derejelerini duýup bilýär we ol topraga dürtülip goýulýar. Programma üpjünçiligine görä, topragyň çyglylyk derejesi gaty pes bolsa, suw nasosy işläp suw turbajyklaryndan suw akmaga başlaýar we tersine çyglylyk ýokary bolsa, suw akmagyny bes edýär. Mundan başga-da ulanyjy islendik wagty akylly telefon arkaly baglary suwaryp biler. 
 
	Ulanylan suwuň we gazyň mukdaryny hasaplamak, aşhana enjamlaryny (peç, howa çekiji) dolandyrmak we bag suwaryş ulgamyny dolandyrmak bularyň ählisi bir programma üpjünçiligine ýüklenildi. Programma üpjünçiligi Python dilinde ýazyldy, we minikompýuteriň iş stolunda saklanylýar.
 
	
	Programmany işe girizmek üçin minikompýuteriň terminalyny açyp, "python3 /Desktop/api/app.py" şu buýrugy (komanda) ýazyp, enter düwmesine basmaly. (Bellik: Flask web serwerine degişli ähli programma üpjünçiligi aýratyn we terminalyň üsti bilen işe girizilýär)

	c) Akylly telefon, planşet, kompýuter tarapyndan iberilýän maglumatlary Raspberry Pi 4 minikompýutere ýetirmek üçin, olaryň hemmesini simsiz aragatnaşyk arkaly bir ýere jemlemeli. Internete birikdirilen islendik Router, simsiz aragatnaşygyny, bir ýere (nokada) jemleýji bolup çykyş edýär. (Bellik: Keseki adamlar bir nokada baglanmaz ýaly, Routere açarsöz (password) goýuň.) Ilki bilen minikompýuter Wi-Fi arkaly Routere birikdirildi. Router, özüne birigen islendik enjama IP-Address berýär. Ol enjamyň özboluşly salgysydyr we ony Routeriň içinde, IP-Address boşlugynda görmek bolýar. Şu wagt 192.168.1.104 ulanylýar. Ol IP-Address üýtgemez ýaly, statiki IP-Address görnüşinde minikompýuteriň ýadyna salyndy. Sebäbi Router birnäçe gezek öçse, başga IP-Address berip biler. Statiki IP-Address bolsa, onuň üýtgemegine ýol bermeýär. Ol şu tertipde ýerine ýetirilýär: terminaly açyp "sudo nano /etc/dhcpcd.conf" buýrugy bermeli, soň penjire açylar, we onuň düzümine 

interface wlan0
static ip_address=192.168.1.104/24
static routers=192.168.1.1
static domain_name_servers=192.168.1.1

goşmaly. Ýatda saklamak üçin, ilki CTRL + X soň Y düwmesine basmaly.

	Flask web serwere degişli ähli programma üpjünçiligini işe girizmeli. Akylly otagy aralykdan dolandyrmak üçin, akylly telefony şol nokada birikdirmeli. Ýöne maglumaty minikompýuteriň şol salgysyna ibermek üçin, akylly telefona programma üpjünçiligi ýazylýar. Bu barada aşakda agzap geçeris.

	d) Öýde tok çeşmesiniň üýtgäp durmagy (öçmegi) zerarly minikompýuteriň işläp duran programmalaryny öçürip bilýär. Ony aradan aýyrmak üçin, minikompýutere skript (programma) ýazyldy. Ol ähli öçürilen programma üpjünçiligini awtomatiki ýagdaýda işe girizýär.
	
	Minikompýuteriň öçüp we ýanyp durmagy bu akylly öýüň ulgamyna gabat gelmeýär. Bu minikompýuterden we birnäçe mikrokontrollerden düzülen ulgama hemişelik aýratyn tok çeşmesi berildi. Ol öýde tok çeşmesi kesilen halatynda-da işlemegini dowam edýär. Tok çeşmesi 12V akkumulýatordan alyndy. Ýöne tutuş ulgam 5V tok çeşmesi bilen iýmitlenýär. Şonuň üçin naprýaženiýa öwrüji inverter goýuldy. Ol tok çeşmesini akkumulýatordan alyp, 12V naprýaženiýany 5V öwürýär we ulgamy iýmitlendirýär. Geçirilen barlaglara görä, doly zarýadly akkumulýator ulgamy minimum 8 sagatlap iýmitlendirmäge ukyply. Akkumulýator hem öýe gelýän tok çeşmesinden zarýadlanyp durýar. Onuň üçin akkumulýatora zarýad beriji enjam ulanyldy. Akkumulýator doly zarýad alandan soň tok çeşmesinden aýrylmasa, onda onuň ulanylyş möhleti azalýar. Meseläni çözmek üçin bir .......... zat ulanyldy. Akkumulýator doly zarýad alan soň, ony tok çeşmesinden ýazdyrýar.

	3. Akylly öý ulgamyny aralykdan dolandyrmak üçin, akylly telefona programma üpjünçiligi ýazyldy. (Java dilinde Android Studio programma üpjünçiliginde ýazyldy, häzirki wagtda android platformasy üçin elýeterli) Programmada basylan her düwmeler iberiji maglumat bolup, olar JSON formatda minikompýutere ugradylýar. Bu ýerde maglumaty ibermek üçin, AsyncTask klasy, HTTP kitaphanalary ulanyldy we ýüklenildi. AsyncTask maglumat iberiji klas bolup, oňa minikompýuteriň salgysy (IP-Address) ýazylýar. HTTP kitaphana bolsa, akylly telefony minikompýuteriň şol salgysyna baglap, maglumat alyş-çalyşygyny ýola goýmaga hyzmat edýär. Ulanmak üçin, akylly telefonyňyzy şol bir Wi-Fi toruna birikdiriň we programma üpjünçiligini işe giriziň. Programma üpjünçiliginiň ulanyjy interfeýsi sada görnüşinde ýerine ýetirildi. Birinji sahypada 3 sany otag, (myhman, okalga, aşhana otagy) kamera we sarp edilen elektrik energiýasy görkezilen. Ikinji sahypada bolsa, ýagtylandyryş, howa sazlaýjy, perde, dürtgüç (rozetka) funksiýalary ýerleşdirilen.
	Diýmek, akylly telefon maglumatlary aralykdan Raspberry Pi 4 minikompýutere ugradýar, ol bolsa maglumaty seljerip, dessine USB kabel arkaly Arduino mikrokontrollere ugradýar we iberilen maglumata görä, akylly otagyň elektrik enjamlaryny dolandyrýar. 

	4. Akylly öý ulgamynyň düzümine şu aşakdaky funksiýalar girýär:
 
    (a)     Ýagtylandyrylyşy dolandyrmak
    (b)     Penjireleri we perdeleri dolandyrmak
    (c)     Howa sazlaýjy ulgamyny dolandyrmak
    (d)     Howpsuzlyk ulgamy
    (e)     Rozetkalary dolandyrmak
    (f)     Wideogözegçilik we domofon
    (g)     Multi otag
    (h)     Suw we gaz syzmalaryň ulgamy
    (i)     Bag suwaryş ulgamy
    (j)     Biometriki howpsuzlyk ulgamy

	(a) Otagyň çyralaryny, RGB LED lentasyny (выключатель) ýa-da akylly telefonyň hem-de  Owaz-20 ses kömekçisi bilen dolandyryp, onuň intensiwligini (pes, orta, ýokary)  hem-de reňkini sazlap bolar. Çyralaryň garyşyk, tebigy ýaly funksiýalar bardyr. Garyşyk funksiýasy çyrany periodiki wagtda ýakyp öçürýär, öýde adam bar ýaly edip görkezýär, tebigy funksiýasy bolsa, daşky sredanyň ýagtylygyna görä otagyň çyralaryny dolandyrýar (daşary ýagty bolsa, çyralaryň intensiwligi peselýär we tersine).  
	Ýerine ýetirilişi: Mikrokontrollere ýazylan programma görä, çyralary (выключатель) ýa-da akylly telefonyň kömegi bilen,  5 režimde ýakyp bilýäris:
    1. Pes ( 1 çyra)
    2. Orta (2 çyra)
    3. Ýokary (3 çyra)
    4. Çyralar + RGB LED
    5. RGB LED
Režimlere geçirmek üçin, (выключатель) basyp we saklamaly, her sekuntdan režimler üýtgäp durar. Gerek režimi saýlamak üçin,  (выключатель) -den eliňizi aýyryň. Çyralary öçürmek üçin, bir gezek (выключатель)  -e basyp we aýyrmak ýeterlikdir.(Çyralara mikrokontroller jogap berýär)

	(b) Penjirelere we perdelere ýazylan programma görä,  akylly telefonyň hem-de  Owaz-20 ses kömekçisi bilen islendik tertipde (pozisiýada, doly, doly däl) açyp we ýapyp bolar. Daşky sredanyň täsiri (ýel, ýagyş, gar) ýetse, penjire awtomatiki ýagdaýda ýapylar. Eger-de otagyň içinde gaz syzmasy duýulsa, onda awtomatiki ýagdaýda açylar. Perde daşky sredanyň ýagtylygyna görä, doly açylyp ýa-da ýapylyp bilner. 
	Ýerine ýetirilişi: Perdäni açyp we ýapyp biler ýaly derejede Stepper motor ulanyldy. Perdäni aňsatlyk bilen aýlar ýaly, stepper motora 2 / 1 baglanyşykda mehanizm ýasaldy.  Stepper motoryň hem-de perdäniň mehanizmini ýörite rezin kemer bilen baglanylýar. Ony ykjam ýagdaýa getirmek üçin 3D printerde gap (daş) ýasaldy. Ulanyjynyň islegine görä, perdäni eliň bilen ýa-da akylly telefonyň kömegi bilen dolandyryp bolar. (Stepper motora mikrokontroller jogap berýär)

	(c) Howa sazlaýjy ulgamyna ýazylan programma görä, akylly telefonyň hem-de  Owaz-20 ses kömekçisi bilen gyzgyn, sowuk, aram tertipde ýa-da temperaturany islendik gradusa sazlap bolar. Onuň tizligini, işleýiş wagtyny hem sazlap bolar. Mundan başga-da otagyň temperaturasyny we çyglylygyny akylly telefonda görüp bolar.
	Ýerine ýetirilişi: Otagdaky merkezi howa sazlaýjy ulgamynyň signallary mikrontrollere birikdirildi. Şeýlelikde ulgamy el ýa-da akylly telefon bilen dolandyryp bolar. (Howa sazlaýjy ulgama mikrokontroller jogap berýär)

	(d) Howpsuzlyk maksady bilen, öý eýesi esasy gapydan girende,  5 sekundyň dowamynda hökmany otagyň (выключатель) -ne basmaly. Şeýle edilende 5 sekuntdan soň işlejek sirenany öçürýär. Tanyş däl keseki adamlar öýe girmekçi bolanlarynda ýa-da öýe girende derrew sirena işläp başlar we eýesiniň ykjam telefonyna sms habary geler.
	Ýerine ýetirilişi: Esasy gapy açylanda Sirena barýan signalyň kontaktlary biri – birine degýär, programma göra, 5 sekuntdan soň sirena işläp başlaýar. SIM 900 modulyň kömegi bilen mikrokontroller öý eýesiniň ykjam telefonyna sms habaryny iberer. Onuň öňüni  almak üçin, çyranyň (выключатель) -ne basmaly. (Howpsuzlyk ulgama mikrokontroller jogap berýär)

	(e) Dürtgüçlere ýazylan programma görä, akylly telefonyň hem-de  Owaz-20 ses kömekçisi bilen awtomatiki ýa-da wagt aralygyna görä (10, 30, 60 minut) dolandyryp bolar. Wagta görä düzülen dürtgüçler  awtomatiki ýagdaýda öçýär.
	Ýerine ýetirilişi: Dürtgüçlere gelýän tok akymy releniň üsti bilen geçýär. Releniň signaly mikrokontrollere barýar we releni dolandyryp bolýar. Mikrokontrollerden rele signal baranda dürtgüçden tok akýar we tersine. (Dürtgüçlere mikrokontroller jogap berýär)

	(f)Akylly telefonyň kömegi bilen hakyky wagtda öýüň içini doly gözegçilik edip bolar. Programmadaky ýörite düwmeler kamerany 4 tarapa öwrüp bilýär. Öýüň daşyndaky adamlar bilen domofon arkaly gürleşip we domofondaky kamera arkaly garşydaşy görüp bolar.
	Ýerine ýetirilişi: ýokarda görkezilen. (Wideogözegçilige minikompýuter jogap berýär)

	(g) Ýazylan programma görä, akylly telefondaky aýdymlary, we ş.m. media faýllary her otagda aýratynlykda, bilelikde açyp we ýapyp bolar. (Onuň üçin, her otagda ses çykaryjynyň (kolonkanyň) bolmagy zerur) Akylly telefona Bluetooth aragatnaşyk arkaly baglanylýar. 
	Ýerine ýetirilişi: Otaglardaky kolonkalara bir ses gataldyjy (usilitel) birikdirildi. Bluetooth ses kabul ediji enjam goýuldy we AUX kabeliň üsti bilen usilitele birikdirildi. (Multi-otaga mikrokontroller jogap berýär)

	(h) Ýörite sensorlar suw ýa-da gaz syzmasyny duýanda, awtomatiki ýagdaýda öýüň içki enjamlaryny dolandyrýar. Mysal üçin, suw syzylanda öýe gelýän suw turbasynyň kranyny ýapýar we eýesine sms habary ugradýar, gaz syzmasy duýulanda bolsa, çyralar öçýär, aýna açylýar, öýe gelýän gaz turbasynyň kranyny ýapýar we eýesine sms habary barýar.
	Ýerine ýetirilişi: Otagda ýörite suw we gaz syzmalary duýýan sensorlar ulanyldy. Öýe gelýän suw hem-de gaz turbasynyň aralygyna elektrik bilen işleýän bekediji klapanlar ulanyldy. Suw ýada gaz syzma baglylykda bekediji klapanlara signal barýar we awtomatiki ýapylýar. SIM 900 modulyň kömegi bilen mikrokontroller öý eýesiniň ykjam telefonyna sms habaryny iberer. (Suw we gaz syzmalaryň ulgamyna mikrokontroller jogap berýär)

	(i) Ösüp oturan baglaryň topragynyň çyglylyk derejesi peselse, awtomatiki ýagdaýda suwaryş ulgamy işläp başlar we tersine.
	Ýerine ýetirilişi: Ýokarda görkezilen. (Bag suwaryş ulgamyna minikompýuter jogap berýär)

	(j) Esasy giriş gapyda fingerprint sensory goýulýar. Diňe programma üpjünçiligine girizilen ulanyjynyň barmak yzy gapyny açyp bilýär. Eger-de öýde elektrik togynyň öçmegi bilen fingerprint sensory işlemedik ýagdaýynda, onda gapyny öz açary bilen açyp bolar. 
	Ýerine ýetirilişi: Fingerprint sensory goýmak üçin, 3D printerde gap (ruçka) ýasaldy. Täze ulanyjynyň barmak yzyny girizmek üçin, gapynyň iç tarapynda gyzyl düwme goýuldy. Arduino Nano mikrokontrolleri ulanyldy, we gapynyň içki boşlugyna salyndy. Diňe programma girizilen barmak yzy gapyny açyp biler. Eger-de keseki adam barmak yzy bilen birnäçe gezek gapyny açmaga synanyşsa, onda fingerprint 5 minudyň dowamynda hiç kimiň barmak yzyny kabul etmez. (Biometriki howpsuzlyk ulgamyna mikrokontroller jogap berýär)




Işi ýerine ýetirmek üçin gerek bolan komponentler:
Raspberry Pi 4 (4GB), Arduino Uno, Arduino Mega, Arduino Nano, Arduino USB cable, ESP 32 Wi-Fi modul, charging adapter 5V / 3A, power supply 12 – 220 V,  USB or Web Camera, fingerprint sensor, DHT 22 sensor, photoresistor, toprak sensor, suw we gaz syzma duýýan sensorlar, stepper motor, 2 servo motor,  suw we gaz bekediji elektrik klapanlar, suw nasos, RGB LED lenta, akkumulýator, inverter, router...