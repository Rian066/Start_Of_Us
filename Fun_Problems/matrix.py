
matrix = [
    [1, 0, 0, 0, 0, 0],
    [0, 1, 0, 1, 1, 1],
    [0, 0, 1, 0, 1, 0],
    [1, 1, 0, 0, 1, 0],
    [1, 0, 1, 1, 0, 0],
    [1, 0, 0, 0, 0, 1],
]

edges = []
def find_edges(matrix):
    global edges
    for index, row in enumerate(matrix):
        if index == 0:
            for i, column in enumerate(row):
                if column == 1:
                    edges.append([0, i])
        if index == (len(matrix) -1):
            for i, column in enumerate(row):
                if column == 1:
                    edges.append([index, i])
        if index != 0 and index != len(matrix) -1:
            if row[0] == 1:
                edges.append([index, 0])
            if row[len(row)-1] == 1:
                edges.append([index, len(row) -1])
    return edges

find_edges(matrix)

def remove_land(matrix):
    visited = []
    for i, row in enumerate(matrix):
        for j, column in enumerate(row):
            if i != 0 and i != len(matrix) -1 and j != 0 and j != len(row) -1 and column == 1:
                if row[j+1] == 0 and row[j-1] == 0 and matrix[i-1][j] == 0 and matrix[i+1][j] == 0:
                    matrix[i][j] = 0
                else:
                    is_1(visited, i, j, matrix)
                    for land in visited:
                        if land in edges:
                            matrix[i][j] = 1
                        else: 
                            matrix[i][j] = 0
    return matrix

def is_1(visited, row, column, matrix):
    if [row, column] in visited:
        return
    visited.append([row,column])

    if row < len(matrix)-1 and matrix[row+1][column] == 1:
        is_1(visited, row+1, column, matrix)
    if row > 0 and matrix[row-1][column] == 1:
        is_1(visited, row-1, column, matrix)
    if column < len(matrix[row])-1 and matrix[row][column+1] == 1:
        is_1(visited, row, column+1, matrix)
    if column > 0 and matrix[row][column-1] == 1:
        is_1(visited, row, column-1, matrix)
    
        

def is_land(row, column):
    global edges
    position = [row, column]

    for edge in edges:
        if edge == position:
            return True
    return False

print(remove_land(matrix))

