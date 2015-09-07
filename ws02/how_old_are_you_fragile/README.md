This program shows very simple integer input from a `std::istream`.

**Note:** This is error prone and not robust. 
Wrong input will cause the std::istream to enter _fail_ mode in which it
stays until `clear()` is called on it.