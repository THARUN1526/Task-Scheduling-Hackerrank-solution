import java.io.*;
import java.math.*;
import java.text.*;
import java.util.*;
import java.util.regex.*;
class Task implements Comparable<Task> {

    public long D;
    public long M;

    public Task(long D, long M) {
        this.D = D;
        this.M = M;
    }

    public int compareTo(Task task) {
        if (this.D < task.D) {
            return -1;
        } else if (this.D > task.D) {
            return 1;
        } else {
            return 0;
        }
    }
}
public class Solution {

    /*
     * Complete the solve function below.
     */
     public static Map<Long, Long> map = new HashMap<Long, Long>();
    public static long maxSoFar = -1;
    public static long deadlineOfMax = -1;
    static long solve(List<Long> tasks, long D, long M, int upIndex) {
        /*
         * Write your code here.
         */
          if (maxSoFar >= 0 && D <= deadlineOfMax) {
            map.put(deadlineOfMax, map.get(deadlineOfMax) + M);
            maxSoFar += M;
            return Math.max(0, maxSoFar);
        }


        if (!map.containsKey(D)) {
            map.put(D, M);
        } else {
           map.put(D, map.get(D) + M);
        }

        if (tasks.size() == 0) {
            tasks.add(D);
            return Math.max(0, M - D);
        } else {
            long total = 0;
            int index = 0;
            long max = -1;
            boolean found = false;
            while (index < tasks.size() &&
                    tasks.get(index) <= D) {
                if (tasks.get(index) == D)
                    found = true;
                total += map.get(tasks.get(index));
                long diff = total - tasks.get(index);
                if (diff > max) {
                    max = diff;
                    maxSoFar = max;
                    deadlineOfMax = tasks.get(index);
                }
                index++;
            }
            if (!found)
                tasks.add(index, D);       // linear, can we avoid this?
            while (index < tasks.size()) {
                total += map.get(tasks.get(index));
                long diff = total - tasks.get(index);
                if (diff > max) {
                    max = diff;
                    maxSoFar = max;
                    deadlineOfMax = tasks.get(index);
                }
                index++;
            }
            return Math.max(0, max);
        }

    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int t = Integer.parseInt(scanner.nextLine().trim());
List<Long> tasks = new ArrayList<Long>(t);
        for (int tItr = 0; tItr < t; tItr++) {
            String[] dm = scanner.nextLine().split(" ");

            int d = Integer.parseInt(dm[0].trim());

            int m = Integer.parseInt(dm[1].trim());

            long result = solve(tasks,d, m, tItr);

            bufferedWriter.write(String.valueOf(result));
            bufferedWriter.newLine();
        }

        bufferedWriter.close();
    }
}