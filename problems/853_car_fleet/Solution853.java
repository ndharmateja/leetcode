import java.util.Arrays;

class Solution853 {
    static class Car implements Comparable<Car> {
        int position;
        double destinationTime;
        int speed;

        public Car(int position, double destinationTime) {
            this.position = position;
            this.destinationTime = destinationTime;
        }

        @Override
        public int compareTo(Car o) {
            return this.position - o.position;
        }
    }

    private double calculateDestinationTime(int position, int speed, int target) {
        return (target - position) / ((double) speed);
    }

    // O(n log n) time and O(1) space solution
    // Reference: https://youtu.be/Pr6T-3yB9RM
    // We are not using a stack like in the reference
    // Method:
    // 1. Sort all the cars based on the position
    // 2. From right to left, for each car we calculate the destination time.
    // 3. If a car on left has a lesser (<=) destination time than the one on right,
    // its destination time will be the same as the car on the right. And therefore
    // be part of the same fleet, as it can't overtake.
    // 4. So we only keep track of the right most car as part of the current fleet
    // and every car that has lesser destination reach time will be part of the
    // same fleet.
    // 5. Once we reach a car that has a higher destination time than the curr car
    // (right most car of the curr fleet), that will be part of a new fleet.
    public int carFleet(int target, int[] positions, int[] speeds) {
        Car[] cars = new Car[positions.length];
        for (int i = 0; i < cars.length; i++) {
            cars[i] = new Car(positions[i], calculateDestinationTime(positions[i], speeds[i], target));
        }
        Arrays.sort(cars);

        int numFleets = 1;
        Car fleetHead = cars[cars.length - 1];
        for (int i = cars.length - 2; i >= 0; i--) {
            // We increment numFleets and start a new fleet
            // only when we find a car with destination time greater
            // than the current fleet head
            // Otherwise we don't do anything
            if (cars[i].destinationTime > fleetHead.destinationTime) {
                numFleets++;
                fleetHead = cars[i];
            }
        }

        return numFleets;
    }
}