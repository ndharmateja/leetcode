-- Nested query
--  Gets the list of product ids that were either sold outside quarter 1 of 2019 or weren't sold at all
SELECT product_id, product_name
FROM Product
WHERE product_id NOT IN (
    SELECT p.product_id
    FROM Product as p LEFT JOIN Sales as s
        ON p.product_id = s.product_id
    WHERE s.sale_date < "2019-01-01"
        OR s.sale_date > "2019-03-31"
        OR s.sale_date IS NULL
);