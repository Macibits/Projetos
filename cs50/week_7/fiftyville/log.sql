-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description -- Get descriprion of duck's robbery.
FROM crime_scene_reports
WHERE year = '2021' AND month = '07' AND day = '28' AND street = 'Humphrey Street';

-- Crime occurred at 10:15 at Humphrey Street bakery, 3 witnesses. Littering at 16:36, 0 witness.

SELECT name, transcript -- Get interviews of witnesses.
FROM interviews
WHERE year = '2021' AND month = '07' AND day = '28';

-- Thief left into car +- 10 minutes after robbery.
-- Thief withdraw money before theft at ATM on Leggett Street.
-- Thief called someone for less a minute, planning take earliest flight 29/07, accompliance will buy flight tickets

SELECT activity, license_plate, minute -- Get security log for local and time of theft.
FROM bakery_security_logs
WHERE year = '2021' AND month = '07' AND day = '28' AND hour = '10';

-- 9 license plate left (exit) bakery after theft.

SELECT account_number, amount, transaction_type, atm_location -- Following who withdraw on Legget Street.
FROM atm_transactions
WHERE year = '2021' AND month = '07' AND day = '28' AND transaction_type = 'withdraw' AND atm_location = 'Leggett Street';

SELECT caller -- Discover phone number which call for less than a minute on theft day.
FROM phone_calls
WHERE year = '2021' AND month = '07' AND day = '28' AND duration < '60';

SELECT passport_number -- Get passport number who leave Fiftyville by morning
FROM passengers
WHERE flight_id IN
(
    SELECT id
    FROM flights
    WHERE year = '2021' AND month = '07' AND day = '29' AND hour < '12' AND origin_airport_id IN
    (
        SELECT id
        FROM airports
        WHERE city = 'Fiftyville'
    )
);

SELECT name -- Join people with leads to intersect thief (and it is Bruce)
FROM people
WHERE license_plate IN
(
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = '2021' AND month = '07' AND day = '28' AND hour = '10' AND minute < '25' AND activity = 'exit'
)
AND id IN
(
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
    (
        SELECT account_number
        FROM atm_transactions
        WHERE year = '2021' AND month = '07' AND day = '28' AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
    )
)
AND phone_number IN
(
    SELECT caller
    FROM phone_calls
    WHERE year = '2021' AND month = '07' AND day = '28' AND duration < '60'
)
AND passport_number IN
(
    SELECT passport_number
    FROM passengers
    WHERE flight_id IN
    (
        SELECT id
        FROM flights
        WHERE year = '2021' AND month = '07' AND day = '29' AND hour < '12' AND origin_airport_id IN
        (
            SELECT id
            FROM airports
            WHERE city = 'Fiftyville'
        )
    )
);

-- The thief is Bruce!

SELECT id, abbreviation, full_name --Infos about Fiftyville airport
FROM airports
WHERE city = 'Fiftyville';
-- Airport id is 8.

SELECT city -- Cities where Bruce possibly escaped.
FROM airports
WHERE id IN
(
    SELECT destination_airport_id
    FROM flights
    WHERE year = '2021' AND month = '07' AND day = '29' AND hour < '12' AND origin_airport_id = '8' AND id IN
    (
        SELECT flight_id
        FROM passengers
        WHERE passport_number IN
        (
            SELECT passport_number
            FROM people
            WHERE name = 'Bruce'
        )
    )
);

-- Bruce escaped to New York City

SELECT id -- Get id from New York airport
FROM airports
WHERE city = 'New York City'
-- Is 4

-- Let's find the accompliance

SELECT phone_number -- Discover Bruce phone number.
FROM people
WHERE name = 'Bruce';

SELECT name -- Who received call with less than a minute of duration from Bruce
FROM people
WHERE phone_number IN
(
    SELECT receiver
    FROM phone_calls
    WHERE year = '2021' AND month = '07' AND day = '28' AND caller = '(367) 555-5533' AND duration < '60'
);

-- Accompliance is Robin