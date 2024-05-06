#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

    float input, decimal;
    int bitLength, integer;
    bool isSigned;
    string stringIn;

//CHECK if INTEGER is already 2expN, if true return consumed bits and proceed to checking DECIMAL
int is2expNleft(bool isSigned, int bitLength, float input)
    {
        // Isolate integer portion of user input
        integer = floor(input);
        decimal = input - integer;
        int match = -1;
        vector<int> num;
        int integerBits = -1;
        int usedBits = 0;

        //Create unsigned lookup vector of valid 2expN elements based on bitLength, be sure to include 2^0.
        // vector[i] index is close to but not exactly the ^N power, (i+1) gets ^N power (for now).
        for (int i=(bitLength - isSigned); i >= 0; i--)
        {
            num.push_back(pow(2,i));
        }

        //Search vector for nearest integer match based on user input, return bits consumed to get user integer step width
        for (int i = num.size() -1 ; i>=0; i--)
        {
            cout << (num.size() - (i + 1)) << " " << (num.at(i) - 1) << endl;
            int temp;
            integerBits = num.size() - (i+1);
            //integerBits -= i;
            temp = num.at(i) - 1;  //check for 1.00, should need 1 integer bit at least, if signed should need 2 bits...
            if(integer == temp)
            {
                match = temp;
                usedBits = integerBits + isSigned;
                cout << "^^^ pefect match" << endl;
                //break;
            }
            else if((integer < temp) && (integer < (pow(2,bitLength) - 1)) && match !=1)
            {
                usedBits = (integerBits) + isSigned;
                cout << "^^^ imperfect match" << endl;
                match = 1;
                //break;
            }

        }

        // TODO If no exact match, will need to bump to nearest see bump2nextInt()
        if(match < 1)
        {
            cout << "XXXX Integer is not 2expN format XXXX" << endl;
        }

        return usedBits;

    }

//TODO Add section for BUMP if integer portion not already 2expN format
//search vector until testvalue is no longer less than [i].  This is the new integer power
//e.g. if test value is 1025, is is greater than 1024, so keep this value (2042, 2^11), return 11 bits
//if a 16 bit example, leaves 5 bits precision for decimal portion.  If 32 bit example... leaves 21 bits for precision.
//decimal precision will max out at 6 sig figs, which is about 2^(-16) anyways, but no need to go beyond for 32 bit.
int bump2nextInt()
{

}

//CHECK if decimal is already in fractional 2^(-N) format i.e. 1/2,1/4,1/8,1/16... 1/65k etc.
//if already in 2^(-N) format, return consumed bits and check against total avaliable for data type.
//if desired >> available bits, bump to next 2^(-N) power that can fit in remaining bits available after INT & SIGN check.
// use a lookup vector like in the INTEGER test.
int is2expNright(int bitLength, float input)
{
        decimal = 0; //just checking if need to reinitialize since declared global above...
        integer = floor(input);
        decimal = input - integer;
        decimal = abs(decimal); // drop sign if exists
        int count = 0;

        // stuff decimal float into stringstream for truncating hidden zeroes and counting digits right of decimal
        std::stringstream ss;
        ss << std::fixed << std::setprecision(6) << decimal;
        std::string str = ss.str();
        if(str.find('.') != std::string::npos)
        {
            str = str.substr(0, str.find_last_not_of('0')+1);
            if(str.find('.') == str.size() -1)
                {
                    str = str.substr(0, str.size() -1);
                }
        }
        count = (str.length() -2);   //drop the leading "0." from the number to get decimal digits count
        if (count < 0){count =0;}
        return count;
}
int bump2nextFrac(float input, int decPlaces, int binBits)
{
//STEPS
//1 Take input value from cin and strip integer off
//2 Compare desirec precision from cin input to available precision remaining after integer test
//3 Create lookup vector of 2expN fractions to N power = (decPlaces + 1)
//3 Search lookup vector to see if input decimal is already in 2expN friendly format
//4 If input decimal is not found in vector, use vector to find nearest win (if tie let even index win)
//5 return valid decimal for re-union with valid integer portion
}
int main()
{

    cout << "Enter Bit Length: " << endl;
    cin >> bitLength;
    cout << "Signed 1, Unsigned 0: " << endl;
    cin >> isSigned;
    cout << "Enter Test Value: " << endl;
    cin >> input;
    cout << endl;

    cout << "User Input: " << input << endl;

    integer = floor(input);
    cout << "Integer portion: " << integer << endl;
    decimal = input - integer;
    cout << "Decimal portion: " << decimal << endl;
    cout << endl;

    int integerBitsUsed;
    int maxDecimalBits;
    int numDecPlaces;

    //CHECK LEFT SIDE: If left side is 2expN valid, return consumed binary bits
    cout << "### CHECK LEFT SIDE ###" << endl;
    integerBitsUsed = is2expNleft(isSigned, bitLength, input);
    cout << "---------------------------------------------------" << endl;
    cout << "[REGISTER]          Total Bits available:          " << bitLength << endl;
    //TODO Only print to screen if valid 2expN integer was found, add case / if clause for message.
    cout << "[SIGNED]            Sign Bit Used:                 " << isSigned << endl;
    cout << "[INTEGER]           Integer Bits Used:             " << (integerBitsUsed - isSigned) << endl;
    cout << "[RANGE]             Total Bits Consumed so far:    " << integerBitsUsed << endl;
    cout << endl;
    //CHECK RIGHT SIDE: If left side valid, see if right side is valid, if so return needed number of base 2 bits req'd to show desired base 10 dec places
    cout << "### CHECK RIGHT SIDE ###" << endl;
    cout << "---------------------------------------------------" << endl;
    numDecPlaces = is2expNright(bitLength, input);
    maxDecimalBits = bitLength - integerBitsUsed;
    cout << "[AVAIL PRECISION]   Base 2 Bits Available:         " << maxDecimalBits << endl;
    cout << "[DESIRED PRECISION] Base 10 Decimal Places Needed: " << numDecPlaces << endl;

    return 0;
}
