def returnIndex(array,number):
    if not array:
        return None
    if len(array) == 1:
        if number > array[0]:
            return 0
        else:
            return None

    si = 0
    ei = len(array)-1
    return binarySearch(array,number,si,ei)

def binarySearch(array,number,si,ei):
    if si==ei:
        if number >= array[si]:
            return si
        else:
            return si-1
    else:
        middle = (ei-si)//2 +si
        if number > array[middle]:
            return binarySearch(array,number,middle+1,ei)
        elif number < array[middle]:
            return binarySearch(array,number,si,middle)
        else:
            return middle

def addJob(length, array, deadline,minutes,late):
    if length < deadline:
        for i in range(deadline-length):
            array.append(i+length)
        length = deadline
    minLeft = minutes
    index = returnIndex(array,deadline-1)
    if index != None:
        while index >=0 and minLeft >0:
            array.pop(index)
            index -= 1
            minLeft -=1
        
    while minLeft >0 and array and array[0] < deadline:
        array.pop(0)
        minLeft -=1
    late += minLeft
    return late,length

if __name__ == '__main__':

    n = int(input().strip())
    
    time = 0
    length = 0
    
    nl = []
    late = 0
    for op in range(n):
        job = input().split(' ')
        late,length = addJob(length,nl,int(job[0]),int(job[1]),late)
        print(late)