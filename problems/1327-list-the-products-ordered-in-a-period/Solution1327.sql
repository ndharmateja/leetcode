SELECT product_name, SUM(unit) as unit
FROM Products p JOIN Orders o
    ON p.product_id = o.product_id
WHERE MONTH(order_date) = 2 AND YEAR(order_date) = 2020
GROUP BY product_name
HAVING SUM(unit) >= 100;