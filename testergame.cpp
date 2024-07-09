#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

class HashTable { 
private:
    struct Node {
        int key;
        Node() : key(-1) {}
    };

    int findNextPrime(int n) {
        while (true) {
            bool isPrime = true;
            for (int i = 2; i * i <= n; i++) {
                if (n % i == 0) {
                    isPrime = false;
                    break;
                }
            }

            if (isPrime) {
                return n;
            }
            ++n;
        }
    }

public:
    vector<Node> table;
    int size;
    HashTable(const vector<int>& dataList) {
        size = findNextPrime(dataList.size());
        table.resize(size);
        initializeTable(dataList);
    }

    void initializeTable(const vector<int>& dataList) {
        for (int i = 0; i < dataList.size(); i++) {
            int hashIndex = dataList[i] % size;

            if (table[hashIndex].key == -1) {
                table[hashIndex].key = dataList[i];
            } else {
                int index = findEmptyRow(hashIndex);
                if (index != -1) {
                    table[index].key = dataList[i];
                }
            }
        }
    }

    int findEmptyRow(int index) {
        int emptyRow = index + 1;
        do {
            if (emptyRow >= size) {
                emptyRow = 0;
            }
            if (table[emptyRow].key == -1) {
                return emptyRow;
            }
            emptyRow += 1;
        } while (emptyRow != index);

        return -1; 
    }

    void displayTable() {
        cout << "index key" << endl;
        for (int i = 0; i < size; ++i) {
            cout << i << "    " << table[i].key << endl;
        }
    }

    int guessIndex(int key) {
        int hashIndex = key % size;

        for (int i = 0; i < size; ++i) {
            int index = (hashIndex + i) % size;

            if (table[index].key == key) {
                return index; // Key found
            }
        }

        return -1; 
    }
};

class HashTableL { 
private:
    struct Node {
        int key;
        int link;
        Node() : key(-1), link(-1) {}
    };

    vector<Node> table;
    int size;

    int findNextPrime(int n) {
        while (true) {
            bool isPrime = true;
            for (int i = 2; i * i <= n; ++i) {
                if (n % i == 0) {
                    isPrime = false;
                    break;
                }
            }

            if (isPrime) {
                return n;
            }
            ++n;
        }
    }

public:
    HashTableL(const vector<int>& dataList) {
        size = findNextPrime(dataList.size());
        table.resize(size);
        initializeTable(dataList);
    }

    void initializeTable(const vector<int>& dataList) {
        for (int i = 0; i < size; ++i) {
            table[i].key = -1;
            table[i].link = -1;
        }

        for (int i = 0; i < dataList.size(); ++i) {
            int hashIndex = dataList[i] % size;

            if (table[hashIndex].key == -1) {
                table[hashIndex].key = dataList[i];
            } else {
                int linkIndex = findEmptyRow(hashIndex);
                if (linkIndex != -1) {
                    table[linkIndex].key = dataList[i];

                    while (table[hashIndex].link != -1) {
                        hashIndex = table[hashIndex].link;
                    }

                    table[hashIndex].link = linkIndex;
                }
            }
        }
    }

    int findEmptyRow(int index) {
        int emptyRow = size - 1;
        do {
            if (table[emptyRow].key == -1) {
                return emptyRow;
            }
            emptyRow -= 1;
        } while (emptyRow >= 0);

        return -1;
    }

    int getSize() const {
        return size;
    }

    int getHash(int index) const {
        return table[index].key;
    }
};

class Hashing {
private:
    unordered_set<string> wordSet;

public:
    Hashing(const vector<string>& words) {
        for (const string& word : words) {
            wordSet.insert(word);
        }
    }
    
    string getRandomWord() {
        auto it = wordSet.begin();
        advance(it, rand() % wordSet.size());
        return *it;
    }

    bool isGameOver(const string& secretWord, const string& guessedWord) {
        return secretWord == guessedWord;
    }
};

class AdventureTree {
public:
    class Node {
    public:
        string message;
        Node* left;
        Node* right;

        Node(const string& msg) : message(msg), left(nullptr), right(nullptr) {}
    };

private:
    Node* root;

public:
    AdventureTree() : root(nullptr) {
        buildTree();
    }

    ~AdventureTree() {
        deleteTree(root);
    }
    char choice2;
    char choice3;
    char choice4;
    char choice5;
    char choice;

    void buildTree() {
        root = new Node("Selamat datang di District 3 (District Teknologi)");
        root->left = new Node("Anda telah memasuki ruangan kantor komunikasi, anda ditawari untuk bekerja di dalam kantor komunikasi tersebut dalam kurun waktu 1 taun. Apakah anda menerima? (y/n)");
        root -> left -> left = new Node ("Selamat! Anda menerima tawaran bekerja dan naik jabatan menjadi Manager. Setelah itu, anda diajak untuk merayakan promosi jabatan anda. Pilih 'k' untuk merayakan di kantor dan pilih 'c' untuk merayakan di cafe restaurant teknologi terkenal di kota tersebut: ");
        root -> left -> right = new Node ("Sayangnya, anda dikira mata-mata dari District 6 dan dihukum mati. Permainan berakhir.");
        root->left->left-> left = new Node ("Karena anda terlalu asik merayakan di kantor bersama dengan teman-teman anda dengan alunan musik yang meriah. Tiba-tiba ruangan kantor selebrasi di tutup dan anda diharuskan bermain permainan tebak angka untuk menebak password dari box yang anda di depan anda tersebut.");
        root->left->left->right = new Node ("Setelah anda makan dengan enak di restaurant tersebut, tiba-tiba bom besar datang dan meledakkan seluruh isi restaurant. Anda tewas. Permainan berakhir");
        root -> left -> left -> left -> right = new Node ("Ternyata itu semua adalah mimpi, dan anda terbangun dari mimpi tersebut. Lalu anda diberitaukan bahwa besok anda akan diantar kedepan pintu keluar District ketiga dan karena anda dianggap telah berjasa di district ketiga, sebagai hadiah anda mendapatkan handphone paling canggih yang ada di district tersebut!.");
        
        root->right = new Node("Anda telah memasuki ruangan bawah tanah, saat anda berjalan di bawah tanah tersebut tiba-tiba anda menginjak sebuah Ponsel Canggih yang tidak pernah anda lihat sebelumnya. Apakah anda akan mengambilnya? (y/n) ");
        root ->right -> right = new Node ("Tiba-tiba handphone tersebut mengeluarkan kata sandi yang harus anda isi dengan memasukkan 1 sampai 2 digit angka. Cepat ! Cari tau berapa kata sandi dari handphone tersebut");
        root -> right -> right -> left = new Node ("Selamat! anda berhasil menebak kata sandi dari handphone tersebut. Anda bisa mengakses handphone tersebut dengan leluasa.Namun, masalah baru, justru datang ... tiba-tiba layar handphone anda berubah menjadi 2 warna, yakni warna biru dan merah. Pilih 'b' untuk warna biru dan 'm' untuk warna merah.");
        root->right->right -> left -> left = new Node ("Anda menekan tombol merah dan ternyata warna dari tombol tersebut merupakan warna kebangsaan dari District 3. Tiba-tiba anda di-teleportasi di depan pintu keluar District 3, dan anda mendapatkan handphone canggih tersebut dan dapat memilih untuk menuju ke District Selanjutnya. Selamat !");
        root->right->right -> left -> right = new Node ("Anda menekan tombol biru dan ternyata warna handphone tersebut memancarkan singyal biru terang dan memanggil monster di bawah tanah tersebut. Anda dikepung monster. Anda tewas. Permainan berakhir!");
        root -> right -> left = new Node ("Setelah anda berjalan meninggalkan handphone tersebut cukup jauh ternyata handphone tersebut mengeluarkan asap dan meledak. Anda tewas. Permainan berakhir");
    }

 void playGame() {
    Node* currentNode = root;

    while (true) {
        cout << "Pilih 'k' untuk ke kantor komunikasi, 'b' untuk ke ruang bawah tanah" << endl;
        cin >> choice;
        while (choice != 'k' && choice != 'b') {
            cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
            cout << "Pilih 'k' untuk ke kantor komunikasi, 'b' untuk ke ruang bawah tanah" << endl;
            cin >> choice;
        }
        if (choice == 'k' && currentNode->left != nullptr) {
            currentNode = currentNode->left;
            cout << currentNode->message << endl;
            cin >> choice2;
            while (choice2 != 'y' && choice2 != 'n') {
                cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                cout << currentNode->message << endl;
                cin >> choice2;
            }
            if (choice2 == 'y' && currentNode->left != nullptr) {
                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                cin >> choice3;
                while (choice3 != 'c' && choice3 != 'k') {
                    cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                    cout << currentNode->message << endl;
                    cin >> choice3;
                }
                if (choice3 == 'c' && currentNode->right != nullptr) {
                    currentNode = currentNode->right;
                    cout << currentNode->message << endl;
                    break;
                } else if (choice3 == 'k' && currentNode->left != nullptr) {
                    currentNode = currentNode->left;
                    cout << currentNode->message << endl;

                    bool main = true;
                    while (main) {
                        main = playTebakAngka();
                    }
                    currentNode = currentNode->right;
                    cout << currentNode->message << endl;
                    break;
                }
            } else if (choice2 == 'n' && currentNode->right != nullptr) {
                currentNode = currentNode->right;
                cout << currentNode->message << endl;
                break;
            }
        } else if (choice == 'b' && currentNode->right != nullptr) {
            currentNode = currentNode->right;
            cout << currentNode->message << endl;
            cin >> choice4;
            
            while (choice4 != 'y' && choice4 != 'n') {
                cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                cout << currentNode->message << endl;
                cin >> choice4;
            }

            if (choice4 == 'y' && currentNode->right != nullptr) {
                currentNode = currentNode->right;
                cout << currentNode->message << endl;
                
                bool main = true;
                while (main) {
                    main = playTebakAngka();
                }

                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                cin >> choice5;

                while (choice5 != 'b' && choice5 != 'm') {
                    cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                    cout << currentNode->message << endl;
                    cin >> choice5;
                }

                if (choice5 == 'b' && currentNode->right != nullptr) {
                    currentNode = currentNode->right;
                    cout << currentNode->message << endl;
                    break;
                } else if (choice5 == 'm' && currentNode->left != nullptr) {
                    currentNode = currentNode->left;
                    cout << currentNode->message << endl;
                    break;
                }
            } else if (choice4 == 'n' && currentNode->left != nullptr) {
                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                break;
            }
        } 
    }
}
    
    bool playTebakAngka() {
        int userGuess;
        int clueCount=10;
        srand(static_cast<unsigned>(time(0)));
        int secretNumber = rand() % 100 + 1; 
        bool loop=true;
        while (loop) {
            cout << "Tebak angka (1-100): ";
            cin >> userGuess;
            clueCount--;
            if (userGuess == secretNumber) {
                cout << "Selamat! Anda berhasil menebak angka dengan benar." << endl;
                return false;
                
            }  
            else if(userGuess < 1 && userGuess > 100){
                cout << "Angka yang dimasukkan tidak valid. Harap masukkan angka antara 1 dan 100." << endl;
                
            }
            else {
            if (clueCount > 0) {
                cout << "Tebakan salah. ";
                
                if (userGuess < secretNumber) {
                    cout << "Angka yang dicari lebih besar. ";
                } else {
                    cout << "Angka yang dicari lebih kecil. ";
                }

                cout << "Sisa kesempatan mendapatkan clue: " << clueCount << endl;
                
            } else {
                cout << "Maaf, kesempatan untuk mendapatkan clue telah habis. Permainan berakhir." << endl;
                loop= false;
                
            }
        }
        }
        return true;
    }

    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
};

class AdventureTree2 {
public:
    class Node {
    public:
        string message;
        Node* left;
        Node* right;

        Node(const string& msg) : message(msg), left(nullptr), right(nullptr) {}
    };

private:
    Node* root;

public:
    AdventureTree2() : root(nullptr) {
        buildTree();
    }

    ~AdventureTree2() {
        deleteTree(root);
    }
        char choice;
        char choice2;
        char choice3;
        char choice4;
        char choice5;
        char choice6;
        char choice7;

    void buildTree() {
        root = new Node("Selamat datang di District 4 (District Tekstil & Warna)");
        root->left = new Node("Anda telah memasuki toko baju Mr. Colour, anda disambut dengan ramah oleh pegawai Mr. Colour yang bernama Mr. Black. Lalu anda ditawari untuk mencoba baju berwarna hitam&putih atau baju warna warni. Tekan 'h' untuk mencoba baju berwarana hitam & putih, dan tekan 'w' untuk mencoba baju berwarana warni (h/w)");
        root -> left -> left = new Node ("Ketika anda mencoba baju berwarna hitam & putih dan anda mengaca di depan kaca anda. Tiba-tiba sekliling anda berubah menjadi sebuah istana mewah dan anda menemui banyak pengawal beserta putri yang cantik. Anda terkesima, apakah anda akan menyapa putri tersebut? (y/n) ");
        root -> left -> right = new Node ("Ketika anda mencoba baju berwarna warni, tiba-tiba baju tersebut berubah menjadi warna hitam seluruhnya dan disekliling anda semuanya berubah menjadi warna hitam dan putih (ups ini adalah rahasia cerita yang tidak boleh diberitaukan kepada siapa-siapa). Karena ternyata District 4 mempunyai warna asli hitam dan putih, anda terjebak di dalam ilusi hitam & putih selamanya. Silakan ulangi permainan!");
        root->left->left->left = new Node ("Karena anda telah menyapa putri tersebut, anda terkesima dengan kecantikan nya yang luar biasa. Lalu, anda dibawak putri tersebut menuju ke kamarnya. Dan disitulah Putri tersebut berubah menjadi penyihir jahat. Anda dibunuh oleh Penyirih. Permainan berakhir!");
        root->left->left->right = new Node ("Karena anda tidak jadi untuk menyapanya. Tiba-tiba anda kepikiran untuk mengikuti putri tersebut ke ruang gantinya, lalu anda terkejut ketika melihat putri tersebut sedang berdandan dan seketika putri tersebut ternyata seorang penyihir dengan berwajah seram. Apakah anda ingin melaporkan kepada pengawal (y/n)");
        root -> left -> left -> right -> left = new Node ("Karena anda tidak melapor kepada pengawal tersebut, saat anda hendak pergi....tiba-tiba anda menjatuhkan sebuah vas bunga di dekat pintu kamar tersebut, dan penyihir tersebut telah mendengarkan. Penyihir tersebut membunuh anda. Anda tewas!");
        root -> left -> left -> right -> right = new Node ("Karena anda memilih untuk melapor ke pengawal ternyata anda malah dibawak ke ruang penjara bawah tanah karena dikira seorang pem-fitnah. Dan pengawal itu mengatakan bahwa putri tersebut akan segera dinobatkan sebagai pewaris tahta District 4 dalam 3 jam lagi. Dan ketika anda berada di penjara, tiba-tiba anda diharuskan untuk memecahkan kata sandi supaya anda bisa keluar dari penjara tersebut. Cepat ! waktu anda tidak lebih dari 3 jam");
        root -> left -> left -> right -> right -> left = new Node ("Karena anda telah berhasil memecahkan kata sandi tersebut, anda bisa keluar dari penjara tersebut. Lalu dengan langkah kaki yang sangat cepat, anda menaiki 100 tangga untuk menuju ke ruang penobatan putri tersebut. Lalu, pada saat anda menaiki tangga ke 76, tiba-tiba anda melihat sebuah buku penyihir ajaib. Dan didalam buku tersebut ada secarik kertas yang berisi mantra ajaib yang ditulis oleh penyihir tersebut. Tanpa, beripikir panjang anda langsung menaiki semua tangga dan telah sampai di depan ruang penobatan tersebut. Dan tiba-tiba anda langsung mengatakan berhenti dengan suara lantang. Lalu, semua pengawal menyergap anda. Apakah anda akan tetap berani mengatakan dengan suara lantang mantra tersebut (y/n)");
        root -> left -> left -> right -> right -> left -> left = new Node ("Karena anda tidak berani mengatakan dengan suara lantang tiba-tiba anda dianggap sebagai pengacau dan dikurung kembali di dalam penjara bawah tanah. Tiba-tiba anda mendengar suara penyihir tersebut karena telah berhasil menguasai district 4 dan dengan seketika semua bangunan runtuh terkena gempa yang dahysat. Dan anda terkena reruntuhan tersebut. Anda tewas ! permainan berakhir");
        root -> left -> left -> right -> right -> left -> right = new Node ("Karena anda berani mengatakan dengan suara lantang tiba-tiba putri tersebut berubah menjadi penyihir. Dan dalam seketika semua pengawal beserta raja mengeluarkan senjata dan menyerang penyihir tersebut. Dan dalam seketika penyihir tersebut berhasil dikalakan. Dan sebagai ucapan terimakasih dari raja, anda diberikan sebuah Armor Perang yang sangat mengkilap dan bagus. Lalu anda diantar oleh raja tersebut untuk menuju ke pintu keluar District 4. Dan anda bisa melanjutkan perjalanan anda");
        
        root->right = new Node("Ketika anda berjalan-jalan di District 4, anda terkesima dengan keindahan warna-warna dari kota tersebut. Lalu ketika anda sudah berjalan cukup jauh, tiba-tiba anda melihat sebuah hutan tropis yang sangat besar. Apakah anda ingin masuk ke dalam hutan tropis tersebut? (y/n)");
        root ->right -> right = new Node ("Karena anda menolak untuk memasuki hutan tropis tersebut, tiba-tiba kota disekiling anda berubah menjadi hitam putih, anda begitu sangat terkejut dengan hal tersebut. Lalu tiba-tiba ada seorang penyihir yang terlihat seperti penyihir amatir merubah anda menjadi kodok. Anda terjebak di dalam tubuh kodok tersebut. Permainan berakhir");
        root -> right -> left = new Node ("Anda telah memberanikan diri memasuki hutan tropis tersebut seorang diri, tiba-tiba anda disambut oleh ketua suku dari hutan tropis tersebut. Namun, karena anda dikira salah satu seorang penyihir juga. Anda diharuskan melewati satu ujian tes dari ketua suku tersebut. Anda dikurung di dalam sebuah kurungan besi, anda diharuskan mencari menebak angka dari kunci kurungan tersebut. Karena menurut kesaksian ketua suku, seorang penyihir tidak bisa menggunakan logika berpikir tentang angka");
        root->right->left->left = new Node ("Ketika anda berhasil menebak kunci tersebut. Ketua suku tersebut sangat senang karena anda adalah seorang manusia bukannya penyihir. Lalu ketua suku tersebut menceritakan sebuah rahasia tentang District 4. Menurut kesaksian ketua suku tersebut, bagian pintu masuk sampai ke tengah kota District 4 telah dikuasai oleh penyihir. Jadi, semua warna indah yang telah anda lihat dari awal pintu masuk sampai di depan hutan semuanya adalah ilusi karena sudah dimanipulasi oleh penyihir. Penyihir tersebut merubah kota yang tadinya indah akan warna warni berubah menjadi warna hitam putih. Lalu, menurut ketua suku tersebut, satu-satunya tempat yang masih belum di manipulasi oleh penyihir tersebut adalah kerajaan pusat District 4 dan saat ini raja tersebut ingin menobatkan putri nya menjadi seorang penerus. Namun, sebenarnya putri tersebut adalah salah satu penyihir jahat yang ingin menguasai District 4. Lalu, anda ditawarkan 2 pilihan oleh ketua suku tersebut, apakah anda ingin membantu ketua suku tersebut untuk membuka kedok dari putri tersebut atau anda akan diantar ke pintu keluar district 4 untuk segera kabur dari tempat ini. (ketik 'k' untuk ke kerajaan dan ketik 'p' untuk ke pintu keluar).");
        root->right->left->left-> right = new Node ("Anda telah diantar ke depan pintu keluar district 4. Lalu tiba-tiba semua kota tersebut berubah menjadi hitam putih, anda terlambat, karena putri tersebut sudah menjadi pewaris kerajaan dan telah menguasai District 4, anda terjebak di dalam kota tersebut selamanya. Permainan berakhir!");
         root->right->left->left-> left = new Node ("Karena anda telah setuju untuk membantu ketua suku tersebut, anda dibekali sebuah mantra ajaib oleh ketua suku tersebut dimana mantra tersebut bisa menguak wajah asli dari penyihir tersebut. Lalu, anda dibawa kedepan cermin ajaib di rumah ketua suku tersebut, dan tiba-tiba anda di teleportasi ke kerjaan tempat penobatan putri tersebut. Tanpa perlu waktu lama, anda langsung membacakan mantra ajaib tersebut, dan seketika putri tersebut berubah menjadi penyihir. Tanpa waktu lama, para pengawal dan raja menyerang penyihir tersebut. Dan setelah itu, raja tersebut mengucapkan terimakasih kepada Anda, dan anda diberikan sebuah Armor Perang yang sangat mengkilap dan kuat. Lalu anda diantar ke depan pintu keluar District 4. Selamat anda berhasil !");
    }

 void playGame() {
    Node* currentNode = root;

    while (true) {
        cout << currentNode->message << endl;
        cout << "Pilih 'w' untuk ke toko baju Mr. Colour, 'p' untuk berjalan-jalan di District 4" << endl;
        cin >> choice;

        while (choice != 'w' && choice != 'p') {
            cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
            cout << "Pilih 'w' untuk ke toko baju Mr. Colour, 'p' untuk berjalan-jalan di District 4" << endl;
            cin >> choice;
        }

        if (choice == 'w' && currentNode->left != nullptr) {
            currentNode = currentNode->left;
            cout << currentNode->message << endl;
            cin >> choice2;
            
            while (choice2 != 'h' && choice2 != 'w') {
                cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                cout << currentNode->message << endl;
                cin >> choice2;
            }

            if (choice2 == 'h' && currentNode->left != nullptr) {
                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                cin >> choice3;
                
                while (choice3 != 'n' && choice3 != 'y') {
                    cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                    cout << currentNode->message << endl;
                    cin >> choice3;
                }

                if (choice3 == 'n' && currentNode->right != nullptr) {
                    currentNode = currentNode->right;
                    cout << currentNode->message << endl;
                    cin >> choice4;

                    while (choice4 != 'y' && choice4 != 'n') {
                        cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                        cout << currentNode->message << endl;
                        cin >> choice4;
                    }

                    if (choice4 == 'y' && currentNode->right != nullptr) {
                        currentNode = currentNode->right;
                        cout << currentNode->message << endl;
                        bool main=true;
                        while(main){
                            main=playTebakAngka();
                        }
                        currentNode = currentNode->left;
                        cout << currentNode->message << endl;
                        cin >> choice5;

                        while (choice5 != 'y' && choice5 != 'n') {
                            cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                            cout << currentNode->message << endl;
                            cin >> choice5;
                        }

                        if (choice5 == 'y' && currentNode->right != nullptr) {
                            currentNode = currentNode->right;
                            cout << currentNode->message << endl;
                            break;
                        } else if (choice5 == 'n' && currentNode->left != nullptr) {
                            currentNode = currentNode->left;
                            cout << currentNode->message << endl;
                            break;
                        }
                    } else if (choice4 == 'n' && currentNode->left != nullptr) {
                        currentNode = currentNode->left;
                        cout << currentNode->message << endl;
                        break;
                    }
                } else if (choice3 == 'y' && currentNode->left != nullptr) {
                    currentNode = currentNode->left;
                    cout << currentNode->message << endl;
                    break;
                }
            } else if (choice2 == 'w' && currentNode->right != nullptr) {
                currentNode = currentNode->right;
                cout << currentNode->message << endl;
                break;
            }
        } else if (choice == 'p' && currentNode->right != nullptr) {
            currentNode = currentNode->right;
            cout << currentNode->message << endl;
            cin >> choice6;

            while (choice6 != 'y' && choice6 != 'n') {
                cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                cout << currentNode->message << endl;
                cin >> choice6;
            }

            if (choice6 == 'y' && currentNode->left != nullptr) {
                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                bool main=true;
                while(main){
                    main=playTebakAngka();
                }
                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                cin >> choice7;

                while (choice7 != 'p' && choice7 != 'k') {
                    cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                    cout << currentNode->message << endl;
                    cin >> choice7;
                }
                if (choice7 == 'p' && currentNode->right != nullptr) {
                    currentNode = currentNode->right;
                    cout << currentNode->message << endl;
                    break;
                } else if (choice7 == 'k' && currentNode->left != nullptr) {
                    currentNode = currentNode->left;
                    cout << currentNode->message << endl;
                    break;
                }
            }

            if (choice6 == 'n' && currentNode->right != nullptr) {
                currentNode = currentNode->right;
                cout << currentNode->message << endl;
                break;
            }
        }
    }
}

   bool isPrime(int number) {
    if (number <= 1) {
        return false;
    }
    for (int i = 2; i <= sqrt(number); ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

int getFirstDigit(int number) {
    return number / 10;
}

bool playTebakAngka() {
    int userGuess;
    int clueCount = 10;
    srand(static_cast<unsigned>(time(0)));
    int secretNumber = rand() % 100 + 1; 
    bool loop = true;

    while (loop) {
        cout << "Tebak angka (1-100): ";
        cin >> userGuess;
        clueCount--;

        if (userGuess == secretNumber) {
            cout << "Selamat! Anda berhasil menebak angka dengan benar." << endl;
            return false;
        }  
        else if (userGuess < 1 || userGuess > 100) {
            cout << "Angka yang dimasukkan tidak valid. Harap masukkan angka antara 1 dan 100." << endl;
        }
        else {
            if (clueCount > 0) {
                cout << "Tebakan salah. ";
                
                if (isPrime(secretNumber)) {
                    cout << "Angka yang dicari adalah bilangan prima. ";
                } else {
                    cout << "Angka yang dicari bukan bilangan prima. ";
                }

                if (secretNumber % 2 == 0) {
                    cout << "Angka yang dicari adalah bilangan genap. ";
                } else {
                    cout << "Angka yang dicari adalah bilangan ganjil. ";
                }

                cout << "Angka depan dari tebak angka adalah: " << getFirstDigit(secretNumber) << ". ";

                cout << "Sisa kesempatan mendapatkan clue: " << clueCount << endl;
            } else {
                cout << "Maaf, kesempatan untuk mendapatkan clue telah habis. Permainan berakhir." << endl;
                loop = false;
            }
        }
    }
    return true;
}
    
    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
};

class AdventureTree3 {
public:
    class Node {
    public:
        string message;
        Node* left;
        Node* right;

        Node(const string& msg) : message(msg), left(nullptr), right(nullptr) {}
    };

private:
    Node* root;

public:
    AdventureTree3() : root(nullptr) {
        buildTree();
    }

    ~AdventureTree3() {
        deleteTree(root);
    }
        char choice;
        char choice2;
        char choice3;
        char choice4;
        char choice5;
        char choice6;
        char choice7;

    void buildTree() {
        root = new Node("Selamat datang di District 5 (District Pertanian)");
        root->left = new Node("Saat anda memilih ke pasar, anda bertemu dengan penjual misterius yang tiba-tiba mengenali anda dan memanggil anda. Apakah anda akan mengunjungi stand penjual tersebut atau tidak? (y/n)");
        root -> left -> left = new Node ("Anda mengunjungi stand penjual tersebut. Dan anda dibertau oleh penjual tersebut untuk menuju ke sawah karena ada satu tugas dari penjaga sawah untuk menemukan bibit ajaib yang berada di sekitar sawah tersebut. Apakah anda akan menerima tugas tersebut (y/n) ");
        root -> left -> right = new Node ("Karena anda tidak mengunjungi stand penjual tersebut. Anda tetap menyusuri pasar tersebut dengan yakin. Lalu, ternyata anda bertemu dengan preman pasar tersebut. Preman tersebut merupakan salah satu bawahan dari Raja di District Ibu Kota, Anda lari ketakutan namun ternyata anda sudah dikepung oleh Preman tersebut dan anda dibunuh. Anda meninggal, silakan ulangi permainan.");
        root->left->left->left = new Node ("Karena anda tidak mau dan tidak yakin akan tugas tersebut, anda akhirnya mengucapkan selamat tinggal kepada penjual tersebut dan lanjut berjalan menelusuri pasar tradisonal tersebut.Lalu, ternyata anda bertemu dengan preman pasar tersebut. Preman tersebut merupakan salah satu bawahan dari Raja di District Ibu Kota, Anda lari ketakutan namun ternyata anda sudah dikepung oleh Preman tersebut dan anda dibunuh. Anda meninggal, silakan ulangi permainan. Permainan berakhir!");
        root->left->left->right = new Node ("Karena anda sudah mengambil tugas dari penjaga stand tersebut, anda akhirnya belok ke kiri dan anda terkesima melihat pemandangan sawah di District 5 yang sungguh memukau. Lalu, anda lagi-lagi bertemu dengan orang asing yang menanyakan identitas anda sebenarnya. Apakah anda ingin memberitaukan identitas anda sepenuhnya? (y/n)");
        root -> left -> left -> right -> left = new Node ("Anda memberitaukan kepada orang asing tersebut siapa anda dan tujuan anda ke District 5, dan juga anda menunjukkan HP Ajaib dan Armor Perang yang sudah anda dapatkan di District-District sebelumnya, dalam seketika anda dibunuh oleh orang asing tersebut karena orang asing tersebut merupakan bawahan dari Raja di District Ibu Kota. Anda tewas, permainan berakhir!");
        root -> left -> left -> right -> right = new Node ("Karena anda tidak menghiraukan orang asing tersebut, anda tetap yakin dan terus maju untuk ke ke tengah sawah, dan di dalam tengah sawah tersebut. Anda disambut oleh penjaga sawah yang telah mengetahui akan kedatangan anda. Tanpa perlu waktu lama, penjaga sawah tersebut memberikan tugas kepada anda untuk mencari salah satu bibit ajaib yang hendak ditanam di sawah tersebut dan menugaskan anda untuk pergi ke gubuk rumah desa yang berada di dekat sawah tersebut. Dan ketika anda telah sampai di gubuk tersebut, anda melihat tumpukan kotak-kotak berurutan yang sudah dilabeli nomer sesuai jumlah kotaknya. Lalu, anda harus memilih salah satu kotak dari keseluruhan kotak tersebut yang berisikan bibit ajaib. Dan anda menemukan secarik kertas yang berisi pesan bahwa anda dapat menebak dimana lokasi bibit ajaib tersebut dengan Hashing dengan metode Linear Probing untuk menebak dimana letak bibit ajaib tersebut.");
        root -> left -> left -> right -> right -> left = new Node ("Anda berhasil menemukan letak dari bibit ajaib tersebut, lalu anda segera bergegas kembali ke tengah sawah dan menemui penjaga sawah tersebut dan penjaga sawah tersebut menanamkan bibit tersebut di dalam tanah. Karena itu adalah bibit ajaib, tiba-tiba bibit tersebut tumbuh dengan cepat dan dengan buah yang sangat banyak. Lalu penjaga sawah tersebut bahagia dengan hal tersebut, dan dengan seketika memetik semua buah tersebut dan segera meng-ekstraknya di gubuk rumahnya. Anda kebingungan akan reaksi penjaga sawah tersebut. Apakah anda akan terus mengikuti penjaga sawah tersebut? (y/n)");
        root -> left -> left -> right -> right -> left -> left = new Node ("Karena anda tidak berani mengikuti penjaga sawah tersebut, tanpa waktu lama ternyata orang asing tersebut mengikuti anda, dan anda dibunuh oleh orang asing tesrebut. Permainan berakhir, anda tewas");
        root -> left -> left -> right -> right -> left -> right = new Node ("Karena anda mengikuti penjaga sawah tersebut, anda dibawah di dalam gubuk miliknya dan anda diminta menunggu sejenak selagi penjaga sawah tersebut meng-ekstrak buah yang telah didapatkan. Dan setelah itu, anda diberikan sebagian dari hasil ekstrak buah tersebut yang sudah berubah menjadi obat ajaib dan berpesan untuk menjaga obat ajaib ini dengan baik-baik. Lalu, anda diantar ke depan pintu keluar District 5 oleh penjaga sawah tersebut sebagai ucapan terimakasih penjaga sawah tersebut. Selamat anda berhasil!");
        
        root->right = new Node("Anda memilih untuk memasuki kampus Pertanian tersebut, dan tiba-tiba anda bertemu dengan salah satu guru di kampus tersebut. Lalu guru tersebut menyambut anda dengan hangat dan mengajak anda untuk memasuki ke ruangan kelas. Namun tiba-tiba guru tersebut mendapatkan panggilan telepon dan dalam seketika anda ditinggal sendirian di lorong lantai kampus tersebut. Anda kebingungan tidak tau jalan... Apakah anda akan memilih lorong kiri atau kanan (l/r)");
        root ->right -> right = new Node ("Anda memberanikan diri untuk menuju ke ruangan kiri dan ternyata di ruangan kiri tersebut hanya ada satu ruangan misterius. Akhirnya, anda memasuki satu-satunya ruangan tersebut. Dan tiba-tiba anda terkejut karena ruangan tersebut merupakan ruangan eksperimen tanaman mematikan dan tanaman tersebut hidup. Lalu, anda dimakan oleh tanaman tersebut. Anda tewas");
        root -> right -> left = new Node ("Karena anda memilih lorong kanan, tiba-tiba anda bertemu dengan salah satu Mahasiswi yang cantik di kampus tersebut. Dan seketika Mahasiswi tersebut mengajak anda untuk melihat fasilitas yang ada di ruang lab (lorong sebelah kanan). Apakah anda mengikuti mahasiswi tersebut? (y/n) ");
        root->right->left->left = new Node ("Anda berani mengikuti mahasiswi tersebut walaupun dengan perasaan yang curiga. Dan dengan waktu yang cepat, tiba-tiba anda juga bertemu dengan guru yang tadi meninggalkan anda. Guru tersebut lalu juga mengajak anda untuk melihat fasilitas yang ada di dalam lab tersebut. Ketika anda memasuki lab tersebut, anda diajak untuk melihat salah satu penelitian yang dilakukan oleh Mahasiswi terpintar yang ada di kampus tersebut. Lalu tiba-tiba ada alarm bahaya karena menurut pengakuan dari guru tersebut ada seorang monster tanaman yang lepas di lorong kiri. Guru dan mahasiswi tersebut langsung bergegas menuju ke lorong kiri, dan anda ditinggal di lab sendirian dan ditugaskan untuk mencari salah satu obat ajaib yang tersimpan di dalam lemari yang berukuran besar dengan banyak pintu lemari. Clue dari menebak pintu tersebut berbentuk Hashing dengan konsep metode Linear Probing untuk menebak obat ajaib tersebut berada di pintu lemari nomer berapa (index ke berapa).");
        root->right->left->right = new Node ("Anda takut mahasiwi tersebut merupakan penyihir sama seperti di petualangan yang telah Anda lalui di District 4. Sehingga, anda memutuskan untuk merubah rute anda ke lorong sebelah kiri. Dan Di lorong sebelah kiri, akhirnya, anda memasuki satu-satunya ruangan tersebut. Dan tiba-tiba anda terkejut karena ruangan tersebut merupakan ruangan eksperimen tanaman mematikan dan tanaman tersebut hidup. Lalu, anda dimakan oleh tanaman tersebut. Anda tewas");
         root->right->left->left-> left = new Node ("Anda telah berhasil menemukan obat tersebut dan bergegas menemui guru dan mahasiswi tersebut, dan adna membantu mereka melawan monster tanaman tersebut. Dalam seketika anda melemparkan obat ajaib tersebut ke tubuh monster itu, lalu monster itu mengeluarkan reaksi ketakutan dan akhirnya mati. Sebagai ucapan terimakasih dai guru tersebut, anda diberika separuh dari obat ajaib tersebut, dan karena anda sudah menemukan item yang dicari. Anda berpamitan dan meminta bantuan kepada guru tersebut untuk mengantarkan anda menuju ke pintu keluar District 5. Tanpa pikir panjang, guru tersebut setuju dan anda telah diantar ke pintu keluar District 5. Selamat anda berhasil!");
    }

 void playGame() {
    Node* currentNode = root;
 
    while (true) {
        cout << currentNode->message << endl;
        cout << "Pilih 'k' untuk ke Kampus Pertanian terkenal di District 5 atau pilih 'p' untuk ke Pasar Tradisional yang ada di District 5" << endl;
        cin >> choice;

        while (choice != 'k' && choice != 'p') {
            cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
            cout << "Pilih 'k' untuk ke Kampus Pertanian terkenal di District 5 atau pilih 'p' untuk ke Pasar Tradisional yang ada di District 5" << endl;
            cin >> choice;
        }

        if (choice == 'p' && currentNode->left != nullptr) {
            currentNode = currentNode->left;
            cout << currentNode->message << endl;
            cin >> choice2;

            while (choice2 != 'y' && choice2 != 'n') {
                cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                cout << currentNode->message << endl;
                cin >> choice2;
            }

            if (choice2 == 'y' && currentNode->left != nullptr) {
                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                cin >> choice3;

                while (choice3 != 'y' && choice3 != 'n') {
                    cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                    cout << currentNode->message << endl;
                    cin >> choice3;
                }

                if (choice3 == 'y' && currentNode->right != nullptr) {
                    currentNode = currentNode->right;
                    cout << currentNode->message << endl;
                    cin >> choice4;
                    
                    while (choice4 != 'n' && choice4 != 'y') {
                        cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                        cout << currentNode->message << endl;
                        cin >> choice4;
                    }

                    if (choice4 == 'n' && currentNode->right != nullptr) {
                        currentNode = currentNode->right;
                        cout << currentNode->message << endl;
                        srand(time(0));
                        cout << "Data Key Table: 27, 18, 29, 28, 39, 13, 16, 42, 17" << endl;
                        playHashTable();
                        currentNode = currentNode->left;
                        cout << currentNode->message << endl;
                        cin >> choice5;

                        while (choice5 != 'y' && choice5 != 'n') {
                            cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                            cout << currentNode->message << endl;
                            cin >> choice5;
                        }

                        if (choice5 == 'y' && currentNode->right != nullptr) {
                            currentNode = currentNode->right;
                            cout << currentNode->message << endl;
                            break;
                        } else if (choice5 == 'n' && currentNode->left != nullptr) {
                            currentNode = currentNode->left;
                            cout << currentNode->message << endl;
                            break;
                        }
                    } else if (choice4 == 'y' && currentNode->left != nullptr) {
                        currentNode = currentNode->left;
                        cout << currentNode->message << endl;
                        break;
                    }
                } else if (choice3 == 'n' && currentNode->left != nullptr) {
                    currentNode = currentNode->left;
                    cout << currentNode->message << endl;
                    break;
                }
            } else if (choice2 == 'n' && currentNode->right != nullptr) {
                currentNode = currentNode->right;
                cout << currentNode->message << endl;
                break;
            }
        } else if (choice == 'k' && currentNode->right != nullptr) {
            currentNode = currentNode->right;
            cout << currentNode->message << endl;
            cin >> choice6;
            
            while (choice6 != 'r' && choice6 != 'l') {
                cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                cout << currentNode->message << endl;
                cin >> choice6;
            }

            if (choice6 == 'r' && currentNode->left != nullptr) {
                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                cin >> choice7;
                
                while (choice7 != 'y' && choice7 != 'n') {
                    cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                    cout << currentNode->message << endl;
                    cin >> choice7;
                }

                if (choice7 == 'y' && currentNode->left != nullptr) {
                    currentNode = currentNode->left;
                    cout << currentNode->message << endl;
                    cout << "Data Key Table: 27, 18, 29, 28, 39, 13, 16, 42, 17" << endl;
                    srand(time(0)); 
                    playHashTable();
                    currentNode = currentNode->left;
                    cout << currentNode->message << endl;
                    break;
                } else if (choice7 == 'n' && currentNode->right != nullptr) {
                    currentNode = currentNode->right;
                    cout << currentNode->message << endl;
                    break;
                }
            }

            if (choice6 == 'l' && currentNode->right != nullptr) {
                currentNode = currentNode->right;
                cout << currentNode->message << endl;
                break;
            }
        } else {
            cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
        }
    }
}
    void playHashTable() {

    int maxAttempts = 5;
    srand(time(0)); 

    while (true) {
    vector<int> dataList = {27, 18, 29, 28, 39, 13, 16, 42, 17};
    HashTable table(dataList);
    int randomIndex = rand() % dataList.size();
    int keyToGuess = dataList[randomIndex];
        int userGuess;
        int attempts = 0;
        bool benar=false;

        cout << "Guess the index for key: " << keyToGuess << endl;

        while (true) {
            cout << "Enter your guess for the index: ";
            while (!(cin >> userGuess)) {
                cout << "Invalid input. Please enter a valid index: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
            int correctIndex = table.guessIndex(keyToGuess);

            if (correctIndex != -1 && userGuess == correctIndex) {
                cout << "Correct! The key " << keyToGuess << " is at index " << correctIndex << endl;
                benar=true;
                break;
            } else {
                cout << "Wrong! ";
                attempts++;
                cout << "You have " << maxAttempts - attempts << " attempts left." << endl;
                if (attempts >= maxAttempts) {
                    cout << "You've reached the maximum number of attempts. The key is at index " << correctIndex << endl;
                    break;
                }
            }
        }
            if(benar){
                break;
            }
        }
    }
    
    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
};

class AdventureTree4 {
public:
    class Node {
    public:
        string message;
        Node* left;
        Node* right;

        Node(const string& msg) : message(msg), left(nullptr), right(nullptr) {}
    };

private:
    Node* root;

public:
    AdventureTree4() : root(nullptr) {
        buildTree();
    }

    ~AdventureTree4() {
        deleteTree(root);
    }
        char choice;
        char choice2;

    void buildTree() {
        root = new Node("Selamat datang di District Ibu Kota, pilih a untuk ke pintu biru atau b untuk pintu merah");
        root->right= new Node("Saat anda memasuki pintu biru ternyata di dalam pintu tersebut sudah ada banyak air beracun yang sudah membanjiri seluruh ruangan dan tiba-tiba semua air tersebut mengenai wajah dan seluruh badan Runner. Dan dalam seketika Runner tewas karena terkena air beracun. Permainan berakhir");
        
        root->left = new Node("Saat anda memasuki pintu merah ternyata di dalam pintu tersebut ada sebuah lorong panjang yang sangat gelap dan kelam. Tetapi di ujung lorong runner melihat suatu cahaya yang sedikit terang. Dan karena Runner membawa baju Armor, maka untuk mempersiapkan sesuatu buruk di depan-nya, Runner membuka tas. Namun, di dalam tas tersebut Runner kebingungan karena banyak saku tas. Runner harus menebak ada di saku keberapa Armor Perang tersebut....");
        root -> left -> left = new Node ("Karena anda berhasil mendapatkan armor, anda mengenakan armor tersebut untuk mempersiapkan diri menghadapi bahaya di depan. Setelah keluar dari lorong, anda menemui Naga di depan sedang tidur, pilih mau membangunkan naga dan melawannya atau diam-diam melewati naga untuk langsung mencari harta karun. Tekan a untuk langsung melawan naga atau b untuk diam-diam mencari hartakarun");
        root -> left -> left -> right = new Node ("Saat sedang diam-diam mengitari naga, tiba-tiba anda menginjak ranting dan membangunkan naga, cepat siapkan diri untuk menghadapi naga!");
        root -> left -> left -> left = new Node ("Anda langsung maju dan berteriak untuk membangunkan naga. Siapkan diri anda untuk menghadapi naga tersebut!");
        root ->left -> left -> right -> left = new Node ("Siapkan senjata anda untuk menyerang, sebelum anda yang diserang. Pakai HP Ajaib dan di dalam HP Ajaib tersebut ada fitur menyerang yang harus dibuka dengan kode yang harus anda tebak. Silakan tebak!");
        root -> left -> left -> left -> left = new Node ("Siapkan senjata anda untuk menyerang, sebelum anda yang diserang. Pakai HP Ajaib dan di dalam HP Ajaib tersebut ada fitur menyerang yang harus dibuka dengan kode yang harus anda tebak. Silakan tebak!");
        root -> left -> left -> left -> left -> left = new Node ("HP ajaib berhasil menyerang Naga dan memberikan critical demage. Karena anda terlalu fokus dengan HP ajaib, anda tidak sadar bahwa naga mendekati anda dan menyerang anda dengan cakarnya. Anda selamat dari serangan fatal karena armor anda, anda kabur dan mencoba untuk menggunakan obat ajaib, sebelum itu anda harus memecahkan kode untuk membuka obat ajaib tersebut");
        root -> left -> left -> right -> left -> left = new Node ("HP ajaib berhasil menyerang Naga dan memberikan critical demage. Karena anda terlalu fokus dengan HP ajaib, anda tidak sadar bahwa naga mendekati anda dan menyerang anda dengan cakarnya. Anda selamat dari serangan fatal karena armor anda, anda kabur dan mencoba untuk menggunakan obat ajaib, sebelum itu anda harus memecahkan kode untuk membuka obat ajaib tersebut");
        root -> left -> left -> left -> left -> left -> left = new Node ("Karena anda sudah sehat kembali, anda harus dengan cepat kembali ke arah naga untuk menghabisinya sebelum dia pulih, cepat gunakan HP ajaib sekali lagi untuk menghabisi naga");
        root -> left -> left -> right -> left -> left -> left = new Node ("Karena anda sudah sehat kembali, anda harus dengan cepat kembali ke arah naga untuk menghabisinya sebelum dia pulih, cepat gunakan HP ajaib sekali lagi untuk menghabisi naga");
        root -> left -> left -> left -> left -> left -> left -> left= new Node ("Selamat, anda telah memberikan serangan fatal 2 kali kepada naga dan telah membunuhnya. Sekarang anda bisa mengambil harta yang dijaga naga itu. Permainan selesai, terimakasih sudah bermain dengan kelompok kami");
        root -> left -> left -> right -> left -> left -> left -> left = new Node ("Selamat, anda telah memberikan serangan fatal 2 kali kepada naga dan telah membunuhnya. Sekarang anda bisa mengambil harta yang dijaga naga itu. Permainan selesai, terimakasih sudah bermain dengan kelompok kami");
    }

 void playGame() {
    Node* currentNode = root;
    vector<int> dataList = {27, 18, 29, 28, 39, 13, 16, 42, 17};
    HashTableL table(dataList);

    while (true) {
        cout << currentNode->message << endl;
        cout << "Pilih a untuk ke pintu warna merah atau pilih b untuk ke pintu warna biru" << endl;
        cin >> choice;
        
        while (choice != 'a' && choice != 'b') {
            cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
            cout << "Pilih a untuk ke pintu warna merah atau pilih b untuk ke pintu warna biru" << endl;
            cin >> choice;
        }

        if (choice == 'a' && currentNode->left != nullptr) {
            currentNode = currentNode->left;
            cout << currentNode->message << endl;
            srand(time(0));
            cout << "Data Key Table: 27, 18, 29, 28, 39, 13, 16, 42, 17" << endl;

            bool loop = true;
            while (loop) {
                loop = playGameL(table);
            }

            currentNode = currentNode->left;
            cout << currentNode->message << endl;
            cin >> choice2;

            while (choice2 != 'a' && choice2 != 'b') {
                cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
                cout << currentNode->message << endl;
                cin >> choice2;
            }

            if (choice2 == 'a' && currentNode->left != nullptr) {
                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                vector<string> words = {"redblacktree", "heaptries", "btree", "hashing", "avltree"};
                Hashing hashingGame(words);
                playHashing(hashingGame);
                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                srand(time(0));
                cout << "Data Key Table: 27, 18, 29, 28, 39, 13, 16, 42, 17" << endl;

                bool loop = true;
                while (loop) {
                    loop = playGameL(table);
                }

                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                srand(time(0));
                cout << "Data Key Table: 27, 18, 29, 28, 39, 13, 16, 42, 17" << endl;
                
                bool loop2 = true;
                while (loop2) {
                    loop2 = playGameL(table);
                }

                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                break;
            }
            else if (choice2 == 'b' && currentNode->right != nullptr) {
                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                vector<string> words = {"redblacktree", "heaptries", "btree", "hashing", "avltree"};
                Hashing hashingGame(words);
                playHashing(hashingGame);
                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                srand(time(0));
                cout << "Data Key Table: 27, 18, 29, 28, 39, 13, 16, 42, 17" << endl;
                
                bool loop = true;
                while (loop) {
                    loop = playGameL(table);
                }

                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                srand(time(0));
                cout << "Data Key Table: 27, 18, 29, 28, 39, 13, 16, 42, 17" << endl;

                bool loop2 = true;
                while (loop2) {
                    loop2 = playGameL(table);
                }

                currentNode = currentNode->left;
                cout << currentNode->message << endl;
                break;
            }
        } else if (choice == 'b' && currentNode->right != nullptr) {
            currentNode = currentNode->right;
            cout << currentNode->message << endl;
            break;
        }
    }
}
    
bool playGameL(const HashTableL& table) {
    srand(static_cast<unsigned int>(time(nullptr)));

    int randomIndex;
    do {
        randomIndex = rand() % table.getSize();
    } while (table.getHash(randomIndex) == -1);


    int targetHash = table.getHash(randomIndex);

    cout << "Anda memiliki 5 kesempatan untuk menebak indeks yang dihasilkan secara acak.\n";
    cout << "Key yang diacak: " << targetHash << endl;

    int guess;
    for (int attempt = 1; attempt <= 5; ++attempt) {
        cout << "Kesempatan ke-" << attempt << ": ";
        while(!(cin >> guess)){
            cout<<"Input a valid answer!: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (guess == randomIndex) {
            cout << "Selamat! Tebakan Anda benar.\n";
            return false;
        } else {
            cout << "Maaf, tebakan Anda salah.\n";
        }
    }

    cout << "Maaf, kesempatan Anda telah habis. Indeks yang benar adalah: " << randomIndex << endl;
    return true;
}

void playHashing(Hashing& hashingGame) {
        string secretWord = hashingGame.getRandomWord();
        string guessedWord(secretWord.length(), '_');
        
        int incorrectAttempts = 0;
        const int maxIncorrectAttempts = 6;
        int hintCount = 2;

        while (incorrectAttempts < maxIncorrectAttempts) {
            cout << "Kata sekarang: " << guessedWord << endl;
            cout << "Jumlah kesempatan menebak: " << maxIncorrectAttempts - incorrectAttempts << endl;

            char guess;
            cout << "Ketik tebakan abjad atau ketik '&' untuk meminta clue: ";
            cin >> guess;

            bool correctGuess = false;

            bool requestHint = (guess == '&' && hintCount > 0);

            if (!requestHint) {
                for (size_t i = 0; i < secretWord.length(); ++i) {
                    if (secretWord[i] == guess) {
                        guessedWord[i] = guess;
                        correctGuess = true;
                    }
                }
            }

            if (!correctGuess && !requestHint) {
                ++incorrectAttempts;
                cout << "Tebakan salah, silakan coba lagi!" << endl;
            } else if (requestHint) {
                if (hintCount > 0) {
                    provideClue(secretWord, guessedWord, hintCount);
                } else {
                    cout << "Tidak ada hint lagi yang bisa diberikan" << endl;
                }
            } else {
                cout << "Tebakan benar!" << endl;
            }

            if (hashingGame.isGameOver(secretWord, guessedWord)) {
                cout << "Selamat anda menebak kata dari kunci tersebut dengan benar: " << secretWord << endl;
                break;
            }
        }

        if (incorrectAttempts == maxIncorrectAttempts) {
            cout << "Maaf, anda telah kehabisan kesempatan kunci nya adalah: " << secretWord << endl;
        }
    }

    void provideClue(const string& secretWord, const string& guessedWord, int& hintCount) {
        for (size_t i = 0; i < secretWord.length(); ++i) {
            if (guessedWord[i] == '_' && hintCount > 0) {
                cout << "Petunjuk: " << secretWord[i] << endl;
                --hintCount;

                if (hintCount == 1) {
                    cout << "Peringatan: Petunjuk anda sisa 1" << endl;
                }
                if (hintCount == 0) {
                    cout << "Petunjuk telah habis jika anda mengetik '&' anda akan dihitung menebak" << endl;
                }

                break;
            }
        }
    }

    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
};

class GraphAdjMatrix {
public:
    int vertices;
    vector<vector<int>> adjMatrix;
    bool isDirected;
    bool isWeighted;

    GraphAdjMatrix(int numVertices, bool isDirected = false, bool isWeighted = false)
    {
        this->vertices = numVertices;
        this->adjMatrix = vector<vector<int>>(numVertices, vector<int>(numVertices, 0));
        this->isDirected = isDirected;
        this->isWeighted = isWeighted;
    }

    void addEdge(int from, int to, int weight = 1) {
        if (from < 0 || from >= this->vertices ||
            to < 0 || to >= this->vertices) {
            cout << "Vertex does not exist\n";
            return;
        }

        if (!this->isWeighted) {
            weight = 1;
        }

        this->adjMatrix[from][to] = weight;

        if (!this->isDirected) {
            this->adjMatrix[to][from] = weight;
        }
    }


    void printGraph()
    {
        for (int i = 0; i < this->vertices; i++)
        {
            for (int j = 0; j < this->vertices; j++)
            {
                cout << this->adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    
    void dijkstra(int startVertex, int endVertex) {
        if (startVertex < 0 || startVertex >= this->vertices || endVertex < 0 || endVertex >= this->vertices) {
            cout << "Invalid vertex\n";
            return;
        }

        vector<int> distance(this->vertices, INT_MAX);
        vector<bool> visited(this->vertices, false);

        distance[startVertex] = 0;

        vector<int> parent(this->vertices, -1);
        parent[startVertex] = startVertex;

        for (int count = 0; count < this->vertices - 1; count++) {
            int u = minDistance(distance, visited);

            visited[u] = true;

            for (int v = 0; v < this->vertices; v++) {
                if (!visited[v] && this->adjMatrix[u][v] && distance[u] != INT_MAX &&
                    distance[u] + this->adjMatrix[u][v] < distance[v]) {
                    distance[v] = distance[u] + this->adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        cout << "Anda berada di kota " << startVertex + 1 << ".\n";
        cout << "Silakan tebak kota tujuan berikutnya (1-7): ";
        int guessedVertex;
        cin >> guessedVertex;

        dijkstra(guessedVertex - 1, endVertex);
    }

    void shortestPath(int startVertex, int endVertex) {
        if (startVertex < 0 || startVertex >= this->vertices || endVertex < 0 || endVertex >= this->vertices) {
            cout << "Invalid vertex\n";
            return;
        }

        vector<int> distance(this->vertices, INT_MAX);
        vector<bool> visited(this->vertices, false);

        distance[startVertex] = 0;

        vector<int> parent(this->vertices, -1);
        parent[startVertex] = startVertex;

        for (int count = 0; count < this->vertices - 1; count++) {
            int u = minDistance(distance, visited);

            visited[u] = true;

            for (int v = 0; v < this->vertices; v++) {
                if (!visited[v] && this->adjMatrix[u][v] && distance[u] != INT_MAX &&
                    distance[u] + this->adjMatrix[u][v] < distance[v]) {
                    distance[v] = distance[u] + this->adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        cout << "Shortest Path from kota " << startVertex + 1 << " to kota " << endVertex + 1 << ":\n";
        printPath(parent, endVertex);
        cout << endl;
    }

    int minDistance(const vector<int>& distance, const vector<bool>& visited) {
        int minDistance = INT_MAX, minIndex;

        for (int v = 0; v < this->vertices; v++) {
            if (!visited[v] && distance[v] <= minDistance) {
                minDistance = distance[v];
                minIndex = v;
            }
        }

        return minIndex;
    }

    void printPath(const vector<int>& parent, int j) {
        if (parent[j] == j) {
            cout << j + 1 << " ";
            return;
        }
        printPath(parent, parent[j]);
        cout << j + 1 << " ";
    }
    
    void playStickmanGame(int startVertex, int endVertex) {
        cout << "Anda berada di District " << startVertex + 1 << ".\n";

        vector<int> shortestPath = findShortestPath(startVertex, endVertex);

        for (int i = 1; i < shortestPath.size(); ++i) {
            int guessedVertex;
            cout << "Silakan tebak kota tujuan berikutnya (1-7): ";
            cin >> guessedVertex;

            if (guessedVertex == shortestPath[i] + 1) {
                cout << "Selamat, jawaban Anda benar!\n";
                if (shortestPath[i] == 2) {
                    AdventureTree adventureTree;
                    adventureTree.playGame();
                    if (adventureTree.choice2 == 'n' || adventureTree.choice3 == 'c' || adventureTree.choice4 == 'n' || adventureTree.choice5 == 'b') {
                        break;
                    }
                }
                else if (shortestPath[i] == 3) {
                    AdventureTree2 adventureTree;
                    adventureTree.playGame();
                    if (adventureTree.choice2 == 'w' || adventureTree.choice3 == 'y' || adventureTree.choice4 == 'n' || adventureTree.choice5 == 'n' || adventureTree.choice6 == 'n' || adventureTree.choice7 == 'p') {
                        break;
                    }
                }
                 else if (shortestPath[i] == 4) {
                        AdventureTree3 adventureTree;
                        adventureTree.playGame();
                        if (adventureTree.choice2 == 'n' || adventureTree.choice3 == 'n' || adventureTree.choice4 == 'y' || adventureTree.choice5 == 'n' || adventureTree.choice6 == 'l' || adventureTree.choice7 == 'n') {
                            break;
                    }
                }
                else if (shortestPath[i] == 6) {
                    AdventureTree4 adventureTree;
                    adventureTree.playGame();
                    if (adventureTree.choice == 'b'){
                        break;
                    }
                }
            }
            else if (guessedVertex == 2) {
                cout << "Maaf, Anda memasuki District 2 yang telah dikuasai oleh monster dan penyihir. Anda Tewas, silakan ulang permainan." << endl;
                break;
            }
            else if (guessedVertex == 6) {
                cout << "Maaf anda telah memasuki Distrik yang dipenuhi monster air dan anda dimakan. Silahkan ulangi permainan." << endl;
                break;
            }
            else {
                cout << "Maaf, Anda masuk ke District yang tidak seharusnya anda kunjungi. Permainan berakhir.\n";
                return;
            }
        }
    }

    vector<int> findShortestPath(int startVertex, int endVertex) {
        vector<int> distance(vertices, INT_MAX);
        vector<bool> visited(vertices, false);

        distance[startVertex] = 0;

        vector<int> parent(vertices, -1);
        parent[startVertex] = startVertex;

        for (int count = 0; count < vertices - 1; ++count) {
            int u = minDistance(distance, visited);

            visited[u] = true;

            for (int v = 0; v < vertices; ++v) {
                if (!visited[v] && adjMatrix[u][v] && distance[u] != INT_MAX &&
                    distance[u] + adjMatrix[u][v] < distance[v]) {
                    distance[v] = distance[u] + adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        vector<int> path;
        int current = endVertex;

        while (current != startVertex) {
            path.push_back(current);
            current = parent[current];
        }

        path.push_back(startVertex);
        reverse(path.begin(), path.end());

        return path;
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    GraphAdjMatrix graph(7, false, true);
    graph.addEdge(0, 1, 2);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 3);
    graph.addEdge(3, 4, 2);
    graph.addEdge(4, 5, 1);
    graph.addEdge(5, 6, 4);
    graph.addEdge(4 ,6, 3);
    graph.addEdge(0, 2, 1);
    graph.addEdge(0, 6, 100);

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Lihat aturan Permainan\n";
        cout << "2. Lihat Peta\n";
        cout << "3. Lihat nama District dan item yang bisa didapatkan\n";
        cout << "4. Mulai Permainan\n";
        cout << "5. Lihat kunci jawaban permainan\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu (1-6): ";
        while(!(cin >> choice)) {
            cout<<"input tidak valid, input ulang: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch (choice) {

            case 1:
                cout << "Selamat datang Runner, anda diharuskan untuk mencapai bos terakhir di kota/district ke 7. Namun diantara ke 7 district tersebut ada beberapa district telah dikuasi oleh Penyihir dan Monster jahat. Runner diharuskan memilih rute terpendek dari district 1 sampai ke 7. Apabila Runner salah memilih kota maka Runner akan gagal dalam permainan ini. Di setiap district yang Runner pilih, Runner akan menghadapi beragam rintangan yang berbeda-beda. Selamat bermain Runner! Semoga anda bisa mencapai tujuan district ke 7." << endl;
                cout << "Jelajahi dunia yang tak terduga, temui petualangan yang memacu adrenaline, dan rebut kunci kemenanganmu dengan keberanian yang tak tergoyahkan." << endl;
                break;
            case 2:
                graph.printGraph();
                break;
            case 3:
                cout << "1. District 2 (District Listrik) : Baterai Abadi" << endl;
                cout << "2. District 3 (District Teknologi) : HP Ajaib" << endl;
                cout << "3. District 4 (District Tekstil & Warna) : Armor Perang" << endl;
                cout << "4. District 5 (District Pertanian) : Obat" << endl;
                cout << "5. District 6 (District Ikan & Air) : Pil Air" << endl;
                cout << "6. District 7 (District Ibu Kota) : Kunci Harta Karun" << endl;
                break;
            case 4:
                graph.playStickmanGame(0,6);
                break;
            case 5:
                int source, destination;
                cout << ("Kunci Jawaban") << endl;
                graph.shortestPath(0, 6);
                break;
            case 6:
                cout << "Terima kasih telah bermain!\n";
                break;
        }

    } while (choice != 6);

    return 0;
}