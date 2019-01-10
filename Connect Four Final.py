def createBoard(N,M):
    grid = [] #sets up the board as an empty array 
    for i in range(N):
        row = [] #adds an extra list each time it runs the sequence
        for j in range(M):
            row.append(0) #adds a zero as the 'empty' space
        grid.append(row)
    return grid

def showBoard(board):
    for i in range(len(board)):
        for j in range(len(board[i])):   
            print(board[i][j], end = " ")
        print()
    print()
    for i in range(len(board[0])):
        print(i, end = " ")
    print()

def draw(board):
    for i in range(len(board[0])):
        if board[0][i] == 0:
            return False
    return True

def checkRow(grid, i, j):
    return grid[i][j] == grid[i][j+1] == grid[i][j+2] == grid[i][j+3] != 0 #if 4 spaces in a row are occupied

def checkColumn(grid, i, j):
    return grid[i][j] == grid[i+1][j] == grid[i+2][j] == grid[i+3][j] != 0 #if 4 space in a column are 

##def checkDiagonal(grid, i, j):
##    return grid [i][j] == grid[i+1][j+1] == grid[i+2][j+2] == grid[i+2][j+2] != 0 
    
      
def checkWin(board, N,M):
    for i in range(N):
        for j in range(M):
            if j + 3 < M and checkRow(board,i,j):

                return True
            elif i + 3 < N and checkColumn(board,i,j):
                return True
##            elif i + j + 3 < N and checkDiagonal(board,i,j):
##                return True
            
    return False 




def main():
    print ('Welcome to connect four!')
    print ('Please choose from the following options:')
    print('1. Play normal connect four \n2. Play with your size board')
    option = int(input('Please select your choice: '))
    if option == 1:
        N = 6
        M = 7
    else:
        N = int(input('How many rows would you like in the grid? '))
        M = int(input('How many columns would you like in the grid? '))
    board = createBoard(N,M)
    player = "Y"
    while True:
        showBoard(board)
        print('It is',player,"'s turn")
        while True:
            try:
                i = input('Enter column to put your piece down: ')
                i = int(i)
                break
            except ValueError:
                print ('No letters allowed, please enter a number')
                
        if i not in range (0,N+1):
            print('Number out of range, please enter a correct number!')
            i = input('Enter column to put your piece down: ')
            i = int(i)
        else:
            i = int(i)
            
        
        for j in range(len(board)):
            if board[N-1 - j][i] == 0:  #reverses the slots and places the counter if empty
                board[N-1 - j][i] = player
                break
            
        if checkWin(board, N, M):
            print('Player', player,'wins!!')
            break
             
        if(draw(board)):
            break       
        
        if player == 'Y':
            player = 'R'
        else:
            player = 'Y'
    showBoard(board)
        
    
    
        
