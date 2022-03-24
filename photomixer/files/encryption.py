#parameters - key, filename, username
import sys
from copy import copy
import copy

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
   

keySchedule = [0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80,0x1B,0x36]


'''
This function replace the matrix with the sbox matrix
Input: matrix
Output: encryted matrix
'''
def subBytes(matrix):
    for row in range(SIZE):
        for column in range(SIZE):
            matrix[row][column] = hex(sbox[int(matrix[row][column], BASE)])
            
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
Output: encryted matrix
'''
def shiftRows(matrix):
    newMatrix = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
    
    for row in range(SIZE):
        newMatrix[row][0] = matrix[row][0]
    
    newMatrix[3][1] = matrix[0][1]

    for row in range(3):
        newMatrix[row][1] = matrix[row+1][1]


    for row in range(2):
        newMatrix[row][2] = matrix[row+2][2]
        newMatrix[row+2][2] = matrix[row][2]
    
    newMatrix[0][3] = matrix[3][3]  
    for row in range(3):
        newMatrix[row+1][3] = matrix[row][3]

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
        if hiBitSet == 0x80:
            a ^= 0x1b
        b >>= 1
        
    return p % 256
 
 
'''
This function mix the columns with the table
Input: matrix
Output: encryted matrix
'''
def mixColumn(matrix):
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
        newMatrix[i] = galoisMult(temp[i],2) ^ galoisMult(temp[i+1],3) ^ galoisMult(temp[i+2],1) ^ galoisMult(temp[i+3],1)
        newMatrix[i+1] = galoisMult(temp[i+1],2) ^ galoisMult(temp[i],1) ^ galoisMult(temp[i+3],1) ^ galoisMult(temp[i+2],3)
        newMatrix[i+2] = galoisMult(temp[i+2],2) ^ galoisMult(temp[i+1],1) ^ galoisMult(temp[i],1) ^ galoisMult(temp[i+3],3)
        newMatrix[i+3] = galoisMult(temp[i+3],2) ^ galoisMult(temp[i+2],1) ^ galoisMult(temp[i+1],1) ^ galoisMult(temp[i],3)
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
This function encryted part of the image pixels each time
Input: key array, hex data array
Output: encryted matrix
'''
def encryptionForEachPart(key, HexArray):
    matrix = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]] 
    arr = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

    #convert the matrix from string to hex
    i = 0   
    for row in range(SIZE):
        for column in range(SIZE):
            matrix[row][column] = hex(HexArray[i])
            i += 1
	
	
    matrix = addRoundKey(keys[0], matrix)

    for round in range(ROUNDS):
        matrix = subBytes(matrix)
        matrix = shiftRows(matrix)
        matrix = mixColumn(matrix)
        key = roundKey(key)
        
        matrix = addRoundKey(keys[round+1], matrix)
       
    matrix = subBytes(matrix)
    matrix = shiftRows(matrix)
    key = roundKey(key)
    

    matrix = addRoundKey(keys[ROUNDS+1], matrix)
	
    #put the matrix in an array
    i = 0   
    for row in range(SIZE):
        for column in range(SIZE):
            arr[i] = matrix[row][column]
            i += 1
       
    return (arr)
    

	
'''
This function encryted the picture pixels
Input: key array, hex array
Output: encryted matrix
'''
def encryption(key, HexArray):
    hexLen = len(HexArray)
    hexKey = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]] 
    textArr = []
    finalEncryption = []
    tempArr = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    k = 0
    i = 0
    j = 0

    #convert the key from string to hex
    for row in range(SIZE):
        for column in range(SIZE):
            hexKey[row][column] = hex(ord(key[i]))
            i += 1

    #turn the array to a two dimensions array
	
    arrLen = hexLen // 16
    leftover = hexLen % 16
    u = 0
    
    for i in range(len(HexArray)):
        if (i % 16 == 0 and i is not 0):
            textArr.insert(j, tempArr)
            tempArr = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
            k = 0
            j += 1
        	
        tempArr[k] = HexArray[i]
        k += 1
        
    global leftOvers
    for i in range(leftover):
        leftOvers.insert(i, HexArray[len(HexArray)-(i+1)])
	
    allRoundsKey(hexKey)
	
    for i in range(len(textArr)):
        temp = encryptionForEachPart(hexKey, textArr[i])
        finalEncryption.insert(i,temp)

    return finalEncryption



def main():
    i = 0
    k = 0
    j = 0
    
    # get the filename
    key = str(sys.argv[1])
    filename = str(sys.argv[2]) 
    username = str(sys.argv[3]) 
    
    fin = open(filename, 'rb')
    image = fin.read()
    fin.close()
    
    image = bytearray(image)
 
    matrix = encryption(key, image)
	
    hex_to_baseE = []
    for i in range(len(matrix)):
        for j in range(16):
            hex_to_baseE.insert(k, matrix[i][j])
            k += 1
	
    base_to_numE = []
    for i in range(len(hex_to_baseE)-1):
        base_to_numE.insert(i, int(hex_to_baseE[i], 16))
	
    byteArrayE = bytearray(base_to_numE) # this is the byte array of the encrypted image

    # create a file with the username's name+matrix
    f = open(username + "\\"+(filename.split("\\")[1]).split(".")[0]+"Matrix.txt", "x")
    f.write(str(base_to_numE))
    f.close()
    
    fin = open(filename, 'wb')
    fin.write(byteArrayE)
    fin.close()
	
	 
if __name__ == "__main__":
    main()