#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

using namespace std;


const int Nb = 4; 
const int Nk = 4; 
const int Nr = 10;


const unsigned char sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

const unsigned char Rcon[11] = {
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

void subBytes(unsigned char state[4][Nb]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < Nb; j++) {
            state[i][j] = sbox[state[i][j]];
        }
    }
}

void shiftRows(unsigned char state[4][Nb]) {
    unsigned char temp;

    temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;


    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    
    temp = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = state[3][0];
    state[3][0] = temp;
}


unsigned char milti(unsigned char a, unsigned char b) {
    unsigned char result = 0;
    unsigned char counter;
    unsigned char hi_bit_set;

    for (counter = 0; counter < 8; counter++) {
        if (b & 1)
            result ^= a;
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set)
            a ^= 0x1b;
        b >>= 1;
    }
    return result;
}

void mixColumns(unsigned char state[4][Nb]) {
    unsigned char temp[4];

    for (int j = 0; j < Nb; j++) {
        for (int i = 0; i < 4; i++) {
            temp[i] = state[i][j];
        }

        state[0][j] = milti(0x02, temp[0]) ^ milti(0x03, temp[1]) ^ temp[2] ^ temp[3];
        state[1][j] = temp[0] ^ milti(0x02, temp[1]) ^ milti(0x03, temp[2]) ^ temp[3];
        state[2][j] = temp[0] ^ temp[1] ^ milti(0x02, temp[2]) ^ milti(0x03, temp[3]);
        state[3][j] = milti(0x03, temp[0]) ^ temp[1] ^ temp[2] ^ milti(0x02, temp[3]);
    }
}

void addRoundKey(unsigned char state[4][Nb], unsigned char* round_key) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < Nb; j++) {
            state[i][j] ^= round_key[i + 4 * j];
        }
    }
}


void keyGen(unsigned char* key, unsigned char* w) {
    unsigned char temp[4];
    unsigned char k;


    for (int i = 0; i < Nk; i++) {
        w[4 * i] = key[4 * i];
        w[4 * i + 1] = key[4 * i + 1];
        w[4 * i + 2] = key[4 * i + 2];
        w[4 * i + 3] = key[4 * i + 3];
    }

    
    for (int i = Nk; i < Nb * (Nr + 1); i++) {
        for (int j = 0; j < 4; j++) {
            temp[j] = w[4 * (i - 1) + j];
        }

        if (i % Nk == 0) {
            
            k = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = k;

            
            temp[0] = sbox[temp[0]];
            temp[1] = sbox[temp[1]];
            temp[2] = sbox[temp[2]];
            temp[3] = sbox[temp[3]];

            temp[0] ^= Rcon[i / Nk];
        }

        for (int j = 0; j < 4; j++) {
            w[4 * i + j] = w[4 * (i - Nk) + j] ^ temp[j];
        }
    }
}


void cryptAES(unsigned char* input, unsigned char* output, unsigned char* key) {
    unsigned char state[4][Nb];
    unsigned char w[4 * Nb * (Nr + 1)];


    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < Nb; j++) {
            state[i][j] = input[i + 4 * j];
        }
    }

    keyGen(key, w);

    addRoundKey(state, w);

    for (int round = 1; round < Nr; round++) {
        subBytes(state);
        shiftRows(state);
        mixColumns(state);
        addRoundKey(state, w + round * 4 * Nb);
    }

    subBytes(state);
    shiftRows(state);
    addRoundKey(state, w + Nr * 4 * Nb);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < Nb; j++) {
            output[i + 4 * j] = state[i][j];
        }
    }
}


void cryptOFB(unsigned char* plaintext, int exampleLen,
    unsigned char* key, unsigned char* iv,
    unsigned char* ciphertext) {
    unsigned char counter[16];
    unsigned char keystream[16];
    int blocks = exampleLen / 16;
    int remaining = exampleLen % 16;

    memcpy(counter, iv, 16);

    
    for (int i = 0; i < blocks; i++) {
        cryptAES(counter, keystream, key);

        for (int j = 0; j < 16; j++) {
            ciphertext[i * 16 + j] = plaintext[i * 16 + j] ^ keystream[j];
        }

        memcpy(counter, keystream, 16);
    }

    if (remaining > 0) {
        cryptAES(counter, keystream, key);
        for (int j = 0; j < remaining; j++) {
            ciphertext[blocks * 16 + j] = plaintext[blocks * 16 + j] ^ keystream[j];
        }
    }
}


void decryptOFB(unsigned char* ciphertext, int ciphertext_len,
    unsigned char* key, unsigned char* iv,
    unsigned char* plaintext) {
    cryptOFB(ciphertext, ciphertext_len, key, iv, plaintext);
}


void printHex(const char* label, unsigned char* data, int len) {
    cout << label;
    for (int i = 0; i < len; i++) {
        cout << hex << setw(2) << setfill('0') << (int)data[i] << " ";
    }
    cout << dec << endl;
}

void AESOFB() {
    unsigned char key[16] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
    };

    unsigned char iv[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    const char* example = "Январь. Пятница. Шесть тридцать вечера. Международный аэропорт имени Линкольна в Иллинойсе был открыт, но все его службы работали с предельным напряжением. Над аэропортом, как и над всеми Средне-Западными штатами, свирепствовал сильнейший буран, какого здесь не было лет пять или шесть. Вот уже трое суток не переставая валил снег. И в деятельности аэропорта, как в больном, измученном сердце, то тут, то там стали появляться сбои. Где-то на летном поле затерялся в снегу пикап «Юнайтед эйрлайнз» с обедами для двухсот пассажиров. Невзирая на снег и наступившую темноту, пикап искали, но пока тщетно – ни машины, ни шофера найти не удалось. Вылет самолета ДС-8 компании «Юнайтед эйрлайнз», для которого пикап вез еду, в беспосадочный рейс на Лос-Анджелес и так уже задерживался на несколько часов. А теперь из-за пропавшего пикапа он вылетит еще позже. Впрочем, это был не единственный случай задержки – около сотни самолетов двадцати других авиакомпаний, пользующихся международным аэропортом Линкольна, не поднялись вовремя в воздух. Объяснялось это тем, что вышла из строя взлетно-посадочная полоса три-ноль: «Боинг-707» авиакомпании «Аэрео Мехикан» при взлете чуть-чуть съехал с бетонированного покрытия и сразу застрял в раскисшей под снегом земле. Вот уже два часа, как люди бились, стараясь сдвинуть с места огромный лайнер. И теперь компания «Аэрео Мехикан», исчерпав собственные ресурсы, обратилась за помощью к «ТВА».";
    int exampleLen = strlen(example);


    int paddedLen = (exampleLen + 15) / 16 * 16;
    unsigned char* plaintext = new unsigned char[paddedLen];
    unsigned char* ciphertext = new unsigned char[paddedLen];
    unsigned char* decrypted = new unsigned char[paddedLen];

    
    memcpy(plaintext, example, exampleLen);
    if (exampleLen < paddedLen) {
        memset(plaintext + exampleLen, 0, paddedLen - exampleLen);
    }

    cout << "AES128 OFB Mode Implementation" << endl;

    printHex("Key:         ", key, 16);
    printHex("IV:          ", iv, 16);
    cout << "Text:     " << example << endl;
    cout << "Text len: " << exampleLen << endl;

 
    cryptOFB(plaintext, paddedLen, key, iv, ciphertext);
    printHex("Ciphertext:   ", ciphertext, paddedLen);

 
    decryptOFB(ciphertext, paddedLen, key, iv, decrypted);
    cout << "Text decrypted: " << decrypted << endl;
    cout << endl;
}
