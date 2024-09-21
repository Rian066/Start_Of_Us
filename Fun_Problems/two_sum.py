def two_sum(nums, target):
    final = []  # Create an array to hold the indexes

    for index, value in enumerate(nums):
        complement = target - value

        if complement in nums:  # If the complemnt is found in nums then just add it to the array and end the loop
            final.append(index)
            final.append(nums.index(complement))
            return final
    

nums = [12, 7, 11, 2, 15]
target = 9
print(two_sum(nums, target))

# Or you can do this:

# def two_sum(nums, target):
#     final = {}

#     for index, value in enumerate(nums):
#         complement = target - value

#         if complement in nums:
#             final[value] = index
#             final[complement] = nums.index(complement)
#             return [final[value], final[complement]]
    
