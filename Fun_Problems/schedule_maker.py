def schedule(p1_schedule, p2_schedule):
    free_time_p1 = []
    free_time_p2 = []
    scheduleable = []
    final_schedule = []

    for index in range(len(p1_schedule) - 1):
        free_time_p1.append(time_covert(p1_schedule[index][1]))
        free_time_p1.append(time_covert(p1_schedule[index+1][0]))
    for i in range(len(free_time_p1) - 3):
        if free_time_p1[i] == free_time_p1[i+1]:
            free_time_p1.pop(i)
            free_time_p1.pop(i)

    # print(free_time_p1)


    for index in range(len(p2_schedule) - 1):
        free_time_p2.append(time_covert(p2_schedule[index][1]))
        free_time_p2.append(time_covert(p2_schedule[index+1][0]))
    for i in range(len(free_time_p2) - 3):
        if free_time_p2[i] == free_time_p2[i+1]:
            free_time_p2.pop(i)
            free_time_p2.pop(i)

    # print(free_time_p2)

    for i in range(len(free_time_p1)):
        if i%2 == 0:
            if free_time_p1[i] > free_time_p2[i]:
                scheduleable.append(to_regular_time(free_time_p1[i]))
            else:
                scheduleable.append(to_regular_time(free_time_p2[i]))
        else:
            if free_time_p1[i] < free_time_p2[i]:
                scheduleable.append(to_regular_time(free_time_p1[i]))
            else:
                scheduleable.append(to_regular_time(free_time_p2[i]))

    for i in range(0, len(scheduleable), 2):
        window = scheduleable[i:i+2]
        final_schedule.append(window)
    
    return final_schedule
    

def time_covert(time):
    time = time.strip("\"")
    newTime = time.split(":")
    hour = int(newTime[0])
    min = int(newTime[1])
    total_mins = hour * 60 + min
    return total_mins

def to_regular_time(time):
    hour, min = divmod(time, 60)
    if min == 0:
        min = "00"
    new_time = str(hour) + ":" + str(min)
    return new_time


test = [["9:00","10:30"],["12:00","13:00"],["16:00","18:00"],["20:00"]]
test2 = [["10:00","11:30"],["12:30","14:30"],["14:30","15:00"],["16:00","17:00"],["18:30"]]

print(schedule(test, test2))