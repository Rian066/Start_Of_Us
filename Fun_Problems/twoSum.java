import java.util.Arrays;

public class twoSum{
    public static void main(String[] args) {
    int[] nums = {2, 12, 11, 7, 15};
    int target = 9;
    System.out.print(Arrays.toString(two_sum(nums, target)));
    }

public static int[] two_sum(int[] nums, int target){
    int[] total = new int[2];
    
    for (int i = 0; i < nums.length; i++){
        int complement = target - nums[i];
        
        for (int j = 0; j < nums.length; j++){
            if (nums[j] == complement){
                total[0] = j;
                total[1] = i;
            }
        }
    }


    return total;

}
}
