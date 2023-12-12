# Givener-encrypter
### This program requires C++17 and x86

To be simple and demonstrative this program has no classes and all functions are in the global namespace.
there are several main parts in the program:

1)alphabet

2)key

3)square

4)function Encrypt()

5)function Decrypt()


### How to use
1) Givener's square consists of alphabets that have different offset. So the user can change his own alphabet or use the default one.
2) user has to invoke the function FillSquare() the parameter is an alphabet. So that the user fills the Givener's square and he is ready to encrypt.
3) set an encryption key, it is a global variable.
4) invoke a function Encrypt(). first parameter is a message, the second one is a key. the function returns std::string (encrypted message)
5) invoke a function Decrypt(). first parameter is a message, the second one is a key. the function returns std::string (decrypted message)

I decided to add some interface to the program in order to use it via Thermux
