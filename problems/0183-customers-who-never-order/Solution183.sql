SELECT name as Customers
FROM Customers LEFT JOIN Orders
    ON Customers.id = Orders.customerId
WHERE Orders.id IS NULL;