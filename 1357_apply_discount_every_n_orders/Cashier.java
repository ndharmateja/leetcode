import java.util.HashMap;
import java.util.Map;

public class Cashier {

    int numCustomers;
    Map<Integer, Integer> pricesMap;
    int n;
    int discount;

    public Cashier(int n, int discount, int[] products, int[] prices) {
        this.numCustomers = 0;
        this.pricesMap = new HashMap<>();
        for (int i = 0; i < products.length; i++) {
            this.pricesMap.put(products[i], prices[i]);
        }
        this.n = n;
        this.discount = discount;
    }

    public double getBill(int[] product, int[] amount) {

        this.numCustomers++;
        boolean hasDiscount = this.numCustomers % n == 0;

        double bill = 0;
        for (int i = 0; i < product.length; i++) {
            bill += this.pricesMap.get(product[i]) * amount[i];
        }

        if (hasDiscount) {
            bill = bill * (100 - discount) / 100;
        }

        return bill;
    }
}
