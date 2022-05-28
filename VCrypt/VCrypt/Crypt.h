#pragma once
#include <string>
#include <iostream>
#include <cstring>

#define BYTESIZE 16
#define BITSIZE 8
#define KEYSCHEDULEAREASIZE 4
#define MAXROUNDNUMBER 10 //temp value

using namespace std;

int** GetOneByteToBinary(int** outputArray, char letter, int byteNumber);

int** GetOneByteToBinary(int** outputArray, int decimal, int byteNumber);

int** GetByteToBinary(int** outputArray, string text, int lastPoint);

int** GetByteToBinary(int** outputArray, int* decimalArray, int lastPoint);

void PrintByteByByte(int** text, int byteNumber);

void PrintAll(int** text, int byteNumber);

int DivideText(int length);

int** SecondDimensionForNewArray(int** text, int byteNumber, int length);

int** CreateNewArray(int** newText, int length);

int** FillArray(int** text, int startPoint, int endPoint);

int** CopyArray(int** getObjArray, int** array);

int** CopyArray(int** getObjArray, int array[BYTESIZE][BITSIZE]);

int** CopyArray(int** getObjArray, int** array, int firstArrayIndex, int secondArrayIndex);

int** CopyArray(int** getObjArray, int** array, int firstArrayIndex, int secondArrayIndex, int firstDimensionLoopSize);

int** CopyBits(int** getObjArray, int** array, int firstArrayIndex, int secondArrayIndex);

int** XOR(int** outputArray, int** inputArray, int outputIndex, int firstIndex, int secondIndex);

int** XOR(int** outputArray, int** inputArray, int outputIndex, int firstIndex, int secondIndex, int loopSize);

int** DecimalToBinary(int** outputArray, int decimal, int index);

int CalculateDecimal(int** text, int i, int startPoint, int loopSize);

int CalculateDecimal(int** text, int i);

char* GetOutputChar(int** encryptedText, int length);

int** SBoxTransactionsForEncryption(int** outputArray);

int** DivideProcessForEncryption(int** inputText, int** outputText, int length);

int** DivideForEncryption(int** forProcessText, int** processText);

int** MergeProcessForEncryption(int** inputText, int** outputText, int length);

int** MergeForEncryption(int** forProcessText, int** processText);

int** EncryptionProcess(int** processText);

int** Encryption(string input, string key);

int** GetInputTextForEncryption(string input, string key);

int** SBoxTransactionsForKey(int** outputArray, int loopSize);

int** VFunction(int** inputText, int** outputText, int numOfRound);

int** AllXORs(int** inputText);

int** KeySchedule(int** inputText, int numOfRound);

int** GetKeyForEncryption(int** keyText, string key, int numOfRound);

int** SBoxTransactionsForDecryption(int** outputArray);

int** DivideProcessForDecryption(int** inputText, int** outputText, int length);

int** DivideForDecryption(int** forProcessText, int** processText);

int** MergeProcessForDecryption(int** inputText, int** outputText, int length);

int** MergeForDecryption(int** forProcessText, int** processText);

int** DecryptionProcess(int** processText);

string Decryption(int* decimalArray, int arrayLength, string key);

string GetInputTextForDecryption(string input, string key);

int** GetKeyForDecryption(int**keyText, string key, int numOfRound);