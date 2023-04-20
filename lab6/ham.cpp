#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Author: Sai Ravi Teja G
// Roll No: SE20UCSE158

// Returns the position of the least significant set bit in a number
int getLSB(int num) {
    return log2(num & -num) + 1;
}

// Encodes the given data using Hamming Code
vector<int> encode(vector<int>& data) {
    int n = data.size();
    int r = 0;
    while ((1 << r) < n + r + 1) {
        r++;
    }

    vector<int> encoded(n + r);
    int j = 0;
    for (int i = 1; i <= n + r; i++) {
        if ((i & (i - 1)) == 0) {
            encoded[i - 1] = 0;
        } else {
            encoded[i - 1] = data[j];
            j++;
        }
    }

    for (int i = 0; i < r; i++) {
        int pos = (1 << i);
        int parity = 0;
        for (int j = pos; j <= n + r; j += 2 * pos) {
            for (int k = 0; k < pos && j + k <= n + r; k++) {
                parity ^= encoded[j + k - 1];
            }
        }
        encoded[pos - 1] = parity;
    }

    return encoded;
}

// Decodes the given data using Hamming Code
bool decode(vector<int>& data) {
    int n = data.size();
    int r = 0;
    while ((1 << r) < n + r + 1) {
        r++;
    }

    vector<int> syndrome(r);
    for (int i = 0; i < r; i++) {
        int pos = (1 << i);
        int parity = 0;
        for (int j = pos; j <= n; j += 2 * pos) {
            for (int k = 0; k < pos && j + k <= n; k++) {
                parity ^= data[j + k - 1];
            }
        }
        syndrome[i] = parity;
    }

    int error_pos = 0;
    for (int i = 0; i < r; i++) {
        error_pos += (syndrome[i] << i);
    }

    if (error_pos > 0) {
        cout << "Error detected at bit position " << error_pos+1 << endl;
        data[error_pos - 1] ^= 1;
        return false;
    } else {
        cout << "No errors in the received data" << endl;
        return true;
    }
}

int main() {
    int n;
    cout << "Enter the number of bits in the input data: ";
    cin >> n;

    vector<int> data(n);
    cout << "Enter the data: ";
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }

    vector<int> encoded = encode(data);
    cout << "Transmitted data (Encoded data or hamming code): ";
    for (int i = 0; i < encoded.size(); i++) {
        cout << encoded[i];
    }
    cout << endl;

    vector<int> received(encoded);
    cout << "Enter the received data: ";
    for (int i = 0; i < received.size(); i++) {
        cin >> received[i];
    }

    decode(received);

    return 0;
}
// 1 1 0 1 0 0 1 1
//  0 1 1 1 1 1 1 0 0 0 1 1


// 1 0 1 1
// 0 1 1 0 0 1 1

