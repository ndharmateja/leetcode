-- Nested query first finds the list of sales person ids that are associated with the company "RED"
SELECT name
FROM SalesPerson
WHERE sales_id NOT IN (
    SELECT sales_id
    FROM Company c JOIN Orders o
        ON c.com_id = o.com_id
    WHERE c.name = "RED"
);