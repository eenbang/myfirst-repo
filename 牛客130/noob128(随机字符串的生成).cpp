//由于C++没有直接支持SHA256加密，我们贴心的花了将近100行代码帮你实现了这个功能。你需要补全的代码在第132行qwq

#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <cmath>
using namespace std;
int enc_len;
string enc_key;

constexpr uint32_t SHA256_K[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

class SHA256 {
private:
    uint32_t m_h[8];
    std::vector<uint8_t> m_buffer;
    uint64_t m_bit_count;

    static uint32_t rotr(uint32_t x, uint8_t n) { return (x >> n) | (x << (32 - n)); }
    static uint32_t ch(uint32_t e, uint32_t f, uint32_t g) { return (e & f) ^ (~e & g); }
    static uint32_t maj(uint32_t a, uint32_t b, uint32_t c) { return (a & b) ^ (a & c) ^ (b & c); }
    static uint32_t sigma0(uint32_t a) { return rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22); }
    static uint32_t sigma1(uint32_t e) { return rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25); }
    static uint32_t gamma0(uint32_t x) { return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3); }
    static uint32_t gamma1(uint32_t x) { return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10); }

    void transform(const uint8_t* data) {
        uint32_t w[64];
        for (int i = 0; i < 16; ++i) {
            w[i] = static_cast<uint32_t>(data[i * 4 + 0]) << 24 |
                   static_cast<uint32_t>(data[i * 4 + 1]) << 16 |
                   static_cast<uint32_t>(data[i * 4 + 2]) << 8 |
                   static_cast<uint32_t>(data[i * 4 + 3]);
        }
        for (int i = 16; i < 64; ++i) {
            w[i] = gamma1(w[i - 2]) + w[i - 7] + gamma0(w[i - 15]) + w[i - 16];
        }

        uint32_t a = m_h[0], b = m_h[1], c = m_h[2], d = m_h[3],
                 e = m_h[4], f = m_h[5], g = m_h[6], h = m_h[7];

        for (int i = 0; i < 64; ++i) {
            uint32_t t1 = h + sigma1(e) + ch(e, f, g) + SHA256_K[i] + w[i];
            uint32_t t2 = sigma0(a) + maj(a, b, c);
            h = g; g = f; f = e; e = d + t1;
            d = c; c = b; b = a; a = t1 + t2;
        }

        m_h[0] += a; m_h[1] += b; m_h[2] += c; m_h[3] += d;
        m_h[4] += e; m_h[5] += f; m_h[6] += g; m_h[7] += h;
    }

public:
    SHA256() {
        reset();
    }

    void reset() {
        m_h[0] = 0x6a09e667; m_h[1] = 0xbb67ae85; m_h[2] = 0x3c6ef372; m_h[3] = 0xa54ff53a;
        m_h[4] = 0x510e527f; m_h[5] = 0x9b05688c; m_h[6] = 0x1f83d9ab; m_h[7] = 0x5be0cd19;
        m_bit_count = 0;
        m_buffer.clear();
    }

    void update(const uint8_t* data, size_t len) {
        for (size_t i = 0; i < len; ++i) {
            m_buffer.push_back(data[i]);
            if (m_buffer.size() == 64) {
                transform(m_buffer.data());
                m_bit_count += 512;
                m_buffer.clear();
            }
        }
    }

    vector<uint8_t> digest() {
        vector<uint8_t> final_buffer(m_buffer);
        m_bit_count += m_buffer.size() * 8;

        final_buffer.push_back(0x80);
        while (final_buffer.size() % 64 != 56) {
            final_buffer.push_back(0x00);
        }

        for (int i = 7; i >= 0; --i) {
            final_buffer.push_back(static_cast<uint8_t>((m_bit_count >> (8 * i)) & 0xFF));
        }

        for (size_t i = 0; i < final_buffer.size(); i += 64) {
            transform(&final_buffer[i]);
        }

        vector<uint8_t> hash(32);
        for (int i = 0; i < 8; ++i) {
            hash[i * 4 + 0] = static_cast<uint8_t>((m_h[i] >> 24) & 0xFF);
            hash[i * 4 + 1] = static_cast<uint8_t>((m_h[i] >> 16) & 0xFF);
            hash[i * 4 + 2] = static_cast<uint8_t>((m_h[i] >> 8) & 0xFF);
            hash[i * 4 + 3] = static_cast<uint8_t>(m_h[i] & 0xFF);
        }

        reset();
        return hash;
    }
};
//返回H(enc)字符串
string H(string enc) {
    // 1. 拼接 key + enc
    string input = enc_key + enc;

    // 2. 计算 SHA256 哈希
    SHA256 sha;
    sha.update(reinterpret_cast<const uint8_t*>(input.data()), input.size());
    vector<uint8_t> hash_bytes = sha.digest();

    // 3. 转为十六进制字符串
    stringstream ss;
    for (uint8_t byte : hash_bytes) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    std::string hex_hash = ss.str();

    // 4. 取前 |enc| 个字符
    return hex_hash.substr(0, enc_len);
}

pair<string, string> solve() {
    //此处补全代码
    std::unordered_map <string,string> mp;
    long long total = pow(26,enc_len);
    string rd(enc_len,' ');
    for(long long x = 0; x < total; x++){
        long long t = x;
        for(int i = enc_len - 1; i >= 0; i--){
            rd[i] = 'a'+ t % 26;
            t /= 26;
        }
        if(mp.count(H(rd))) return {mp[H(rd)],rd};//用bool标记或者双次判断break或者goto end_loops   end_loops:.....
        mp[H(rd)] = rd;
     
    }
        
    
}
/*随机数生成方法
  1. random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 25);
    后面用distrib(gen)生成就是随机数0~25；
  2. 二十六进制法，如本题答案如此（忘记了可以从简单的两位进行举例！！！！）
*/



int main() {
    cin >> enc_len >> enc_key;
    auto result = solve();
    cout << result.first << " " << result.second << endl;
    return 0;
}