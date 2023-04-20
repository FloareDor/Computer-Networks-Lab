#include <iostream>
#include <string>

using namespace std;

string crc(string input, string divisor) {
    int input_len = input.length();
    int divisor_len = divisor.length();
    int padding = divisor_len - 1;
    string dividend = input;
    for (int i = 0; i < padding; i++) {
        dividend += "0";
    }
    for (int i = 0; i <= input_len; i++) {
        if (dividend[i] == '1') {
            for (int j = 0; j < divisor_len; j++) {
                dividend[i + j] = (dividend[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }
    return dividend.substr(input_len, padding);
}

int main() {
    string input;
    string divisor;
    int input_len;
    int divisor_len;

    cout << "Enter the number of bits in input data: ";
    cin >> input_len;
    cout << "Enter the number of bits in the polynomial generator (divisor): ";
    cin >> divisor_len;
    cout << "Enter the data: ";
    cin >> input;
    cout << "Enter the divisor: ";
    cin >> divisor;

    string crc_value = crc(input, divisor);
    string transmitted_data = input + crc_value;
    string received_data;

    cout << "CRC value: " << crc_value << endl;
    cout << "Transmitted data: " << transmitted_data << endl;
    cout << "Enter the received data: ";
    cin >> received_data;

    string received_crc_value = crc(received_data.substr(0, input_len), divisor);
    
    if (received_crc_value == received_data.substr(input_len)) {
        cout << "No errors detected" << endl;
    } else {
        cout << "Errors detected" << endl;
        cout << "Non zero remainder: " << received_crc_value << endl;
    }

    return 0;
}

// 1010001101
// 110101
// 101000110101110


// 1010001101
// 110101
// 101001110101110