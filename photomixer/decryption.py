#parameters - file pixels(bytearray), key, filename, username
import sys
from copy import copy
import copy
import os

SIZE = 4
BASE = 16
ROUNDS = 9

count = 0
keys = [[0], [0], [0], [0],[0], [0], [0] ,[0], [0], [0], [0]]
changeLastArrKey = [0]

leftOvers = []

sbox = [
   0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
   0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
   0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
   0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
   0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
   0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
   0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
   0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
   0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
   0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
   0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
   0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
   0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
   0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
   0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
   0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16]
   

   
sboxInverse = [
        0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
        0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
        0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
        0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
        0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
        0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
        0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
        0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
        0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
        0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
        0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
        0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
        0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
        0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
        0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
        0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d]

keySchedule = [0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80,0x1B,0x36]


'''
This function replace the matrix with the sboxInverse matrix
Input: matrix
Output: encryted matrix
'''	
def inverseSubBytes(matrix):
    for row in range(SIZE):
        for column in range(SIZE):
            matrix[row][column] = hex(sboxInverse[int(matrix[row][column], BASE)])
            
    return matrix


'''
This function replace the arr with the sbox matrix
Input: arr
Output: decryted arr
'''
def subBytesForAddRoundKey(arr):
    for column in range(SIZE):
        index = int(arr[column], BASE)
        arr[column] = hex(sbox[index])
            
    return arr


'''
This function shift the rows
Input: matrix
Output: decryted matrix
'''
def inverseShiftRows(matrix):
    newMatrix = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
    
    for row in range(SIZE):
        newMatrix[row][0] = matrix[row][0]
		
    newMatrix[0][1] = matrix[3][1]
	
    for row in range(SIZE):
        newMatrix[row][1] = matrix[row-1][1]
		
		
    for row in range(2):
        newMatrix[row][2] = matrix[row-2][2]
        newMatrix[row-2][2] = matrix[row][2]
		
    
    newMatrix[3][3] = matrix[0][3]  
    for row in range(SIZE):
        newMatrix[row-1][3] = matrix[row][3]
		
    return(newMatrix) 


'''
This is a help function for mixColumns
Input: int number from matrix, int number from table
Output: result
'''
def galoisMult(a, b):
    p = 0
    hiBitSet = 0
    
    for i in range(8):
        if b & 1 == 1:
            p ^= a
        hiBitSet = a & 0x80
        a <<= 1
        if (hiBitSet == 0x80):
            a ^= 0x1b
        b >>= 1
        
    return p % 256
    
    
'''
This function change the key
Input: key matrix
Output: new key matrix
'''
def roundKey(key):   
    newKey = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]  
    
    temp = copy.deepcopy(key[SIZE-1])
    gKey = g(key[SIZE-1])
    
    for column in range(SIZE):
        newKey[0][column] = hex(int(key[0][column], BASE) ^ int(gKey[column], BASE)) #xor
        
    for column in range(SIZE):
        newKey[1][column] = hex(int(newKey[0][column], BASE) ^ int(key[1][column], BASE)) #xor
        
    for column in range(SIZE):
        newKey[2][column] = hex(int(newKey[1][column], BASE) ^ int(key[2][column], BASE)) #xor
        
    for column in range(SIZE):
        newKey[3][column] = hex(int(newKey[2][column], BASE) ^ int(temp[column], BASE)) #xor
       
    return (newKey)
 

 
'''
This function mix the columns with the table
Input: matrix
Output: decrypted matrix
'''
def inverseMixColumn(matrix):
    #put the two dimensions array in a one dimension array
    newMatrix = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    i = 0
    for row in range(SIZE):
        for column in range(SIZE):
            newMatrix[i] = int(matrix[row][column], BASE)
            i += 1


    #mix the matrixs
    i = 0
    temp = copy.copy(newMatrix)
    for times in range(SIZE):
        newMatrix[i] = galoisMult(temp[i],14) ^ galoisMult(temp[i+1],11) ^ galoisMult(temp[i+2],13) ^ galoisMult(temp[i+3],9)
        newMatrix[i+1] = galoisMult(temp[i+1],14) ^ galoisMult(temp[i],9) ^ galoisMult(temp[i+3],13) ^ galoisMult(temp[i+2],11)
        newMatrix[i+2] = galoisMult(temp[i+2],14) ^ galoisMult(temp[i+1],9) ^ galoisMult(temp[i],13) ^ galoisMult(temp[i+3],11)
        newMatrix[i+3] = galoisMult(temp[i+3],14) ^ galoisMult(temp[i+2],9) ^ galoisMult(temp[i+1],13) ^ galoisMult(temp[i],11)
        i += SIZE
           
    #convert from int to hex
    i = 0
    for row in range(SIZE):
        for column in range(SIZE):
            matrix[row][column] = hex(newMatrix[i])
            i += 1
         
    return (matrix)
    
    
'''
This function add the key to the matrix
Input: key array, matrix
Output: encryted matrix
'''
def addRoundKey(key, matrix):
    newMatrix = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]

    #add the key to the matrix
    for row in range(SIZE):
        for column in range(SIZE):
            newMatrix[row][column] = hex(int(matrix[row][column], BASE) ^ int(key[row][column], BASE)) #xor
			
    return (newMatrix)
    
    
    
'''
This function will get all the roundkeys 1-10 and put them into  a global arr
input: key (the first key)
output: none
'''
def allRoundsKey(key):
    temp = copy.deepcopy(key)
	
    global keys
    keys[0] = copy.deepcopy(key)
    keys[1] = roundKey(copy.deepcopy(keys[0]))
    keys[2] = roundKey(copy.deepcopy(keys[1]))
    keys[3] = roundKey(copy.deepcopy(keys[2]))
    keys[4] = roundKey(copy.deepcopy(keys[3])) 
    keys[5] = roundKey(copy.deepcopy(keys[4]))
    keys[6] = roundKey(copy.deepcopy(keys[5]))
    keys[7] = roundKey(copy.deepcopy(keys[6]))
    keys[8] = roundKey(copy.deepcopy(keys[7]))
    keys[9] = roundKey(copy.deepcopy(keys[8]))
    keys[10] = roundKey(copy.deepcopy(keys[9]))
 
 
'''
This is a help function for roundKey
Input: last column of the key matrix
Output: the column
'''
def g(column):    
    global count
    
    temp = column[0]
    column[0] = column[1]
    column[1] = column[2]
    column[2] = column[3]
    column[3] = temp
    
    column = subBytesForAddRoundKey(column)

    column[0] = hex(keySchedule[count] ^ int(column[0], BASE))   
    count += 1
    if (count == 10):
        count = 0
           
    return (column) 
    

'''
This function decryted part of the image pixels each time
Input: key array, hex data array
Output: decryted matrix
'''
def decryptionForEachPart(key, HexArray):
    index = ROUNDS
    matrix = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]] 
    arr = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

    #print(HexArray)
    #convert the matrix from string to hex
    i = 0   
    for row in range(SIZE):
        for column in range(SIZE):
            matrix[row][column] = hex(HexArray[i])
            i += 1
            
    matrix = addRoundKey(copy.deepcopy(keys[ROUNDS+1]), matrix) 	
    for round in range(ROUNDS):
        matrix = inverseShiftRows(matrix) 
        matrix = inverseSubBytes(matrix)
        
        #use the key from the keys array
        #key  = keys[index]

        matrix = addRoundKey(copy.deepcopy(keys[index]), matrix)
        index -= 1
        matrix = inverseMixColumn(matrix)	
        #print(str(round) , " ")
     
    matrix = inverseShiftRows(matrix)
    matrix = inverseSubBytes(matrix)
    matrix = addRoundKey(copy.deepcopy(keys[0]), matrix)
    
	
    #put the matrix in an array
    i = 0   
    for row in range(SIZE):
        for column in range(SIZE):
            arr[i] = matrix[row][column]
            i += 1
    
    return (arr)
	




'''
This function decryted the picture pixels
Input: key array, hex array
Output: decryted matrix
'''
def decryption(key, HexArray):            
    finalDecryption = []
    tempArr = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    i = 0
    #print(HexArray)
    for i in range(len(HexArray)):
        temp = decryptionForEachPart(key, HexArray[i])
        finalDecryption.insert(i,temp)
   
    return finalDecryption



def main():
    #print(sys.argv)

    # get the encriped pixels and keys and dilename
    global keys
    key = str(sys.argv[1])
    filename = str(sys.argv[2])
    username = str(sys.argv[3])
    
    # get datat from file
    file = open(username + "Matrix.txt", 'r')
    text = str(file.read())
    file.close()
    os.remove(username + "Matrix.txt")
    
    text = text[1:-1]
    text = text.split(",")
    myList = []
    for i in range(len(text)):
        myList.insert(i, int(text[i]))
        
    

    
    #myString = text.decode("utf-8") 
    #matrix = myString 
    
    #encode_string = text.encode()
    #matrix = bytearray(encode_string)
    #matrix = text
	
    # decryption
    toDecryption = []
    tempArr = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    hexKey = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]] 
    i = 0
    k = 0
    j = 0
    
    #convert the key from string to hex
    for row in range(SIZE):
        for column in range(SIZE):
            hexKey[row][column] = hex(ord(key[i]))
            i += 1
    allRoundsKey(hexKey)


    for i in range(len(myList)):
        if (i % 16 == 0 and i is not 0):
            toDecryption.insert(j, tempArr)
            tempArr = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
            k = 0
            j +=1
        tempArr [k] = myList[i]
        k +=1
       
           
    #print(toDecryption)     
    matrix2 = decryption(keys[ROUNDS+1], toDecryption)
    #print("decryption: ", matrix2)
    #print(" ")
	
    i = 0
    k = 0
    j = 0
	
	
	# back to the picture
    hex_to_baseD = []
    for i in range(len(matrix2)):
        for j in range(16):
            hex_to_baseD.insert(k, matrix2[i][j])
            k += 1
	
    base_to_numD = []
	
    for i in range(len(hex_to_baseD)-1):
        base_to_numD.insert(i, int(hex_to_baseD[i], 16))
	
    byteArrayD = bytearray(base_to_numD) # this is the byte array of the decrypted image
	
	
    fin = open(filename, 'wb')
    fin.write(byteArrayD)
    fin.close();
	
	 
if __name__ == "__main__":
    main()