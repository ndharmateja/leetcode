-- Solution 1:
-- Nested query:
--  Gets the unique list of (user_id, activity_date) combinations
--  in the given time period.
SELECT activity_date as day, COUNT(*) as active_users
FROM (
    SELECT DISTINCT user_id, activity_date
    FROM Activity
    WHERE DATEDIFF("2019-07-27", activity_date) < 30
        AND "2019-07-27" >= activity_date
) as UserDates
GROUP BY activity_date
ORDER BY day;

-- Solution 2:
SELECT 
    activity_date as day, 
    COUNT(DISTINCT user_id) as active_users
FROM Activity
WHERE DATEDIFF("2019-07-27", activity_date) < 30
    AND "2019-07-27" >= activity_date
GROUP BY activity_date;
