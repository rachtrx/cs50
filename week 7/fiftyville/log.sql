-- Keep a log of any SQL queries you execute as you solve the mystery.

-- find the report ID by filtering based on the date and street
SELECT id, description
  FROM crime_scene_reports
 WHERE street = 'Humphrey Street'
   AND year = 2021
   AND month = 7
   AND day = 28; -- returns report #295, time 10:15am, 3 interviews were conducted

-- find the 3 interviews and filter based on 'bakery' and date
SELECT *
  FROM interviews
 WHERE transcript LIKE '%bakery%'
   AND year = 2021
   AND month = 7
   AND day = 28;

-- Ruth: the car exited between 10:15 and 10:25
-- Check cars exiting between 10:15 and 10:25
SELECT license_plate
  FROM bakery_security_logs
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND hour = 10
   AND minute >= 15
   AND minute <= 25
   AND activity = 'exit';
   -- license plates are | 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55

-- Eugene: thief withdrew money from ATM on Leggett Street earlier that morning
-- find people who have accounts that did withdrawal ATM transactions before 10.15 at Leggett Street

SELECT name
  FROM atm_transactions
       JOIN bank_accounts
       ON atm_transactions.account_number = bank_accounts.account_number
       JOIN people
       ON bank_accounts.person_id = people.id
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND atm_location LIKE 'leggett street'
   AND transaction_type = 'withdraw';
-- Account numbers: 28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199

-- Raymond: The thief made a <1min phone call as he left, planning to take earliest flight
-- out on July 29, and asked the accomplice to purchase the ticket
-- get caller and receiver phone calls under 1min from 10.15 to 10.25
SELECT caller
  FROM phone_calls
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND duration < 60;
-- Callers: (130) 555-0289, (499) 555-9472, (367) 555-5533, (499) 555-9472, (286) 555-6063, (770) 555-1861, (031) 555-6622, (826) 555-1652, (338) 555-6650

-- check for passport numbers for earliest flight out of Fiftyville on July 29
SELECT DISTINCT(passport_number)
  FROM airports
       JOIN flights
       ON airports.id = flights.origin_airport_id
       JOIN passengers
       ON flights.id = passengers.flight_id
 WHERE flights.id =
       (SELECT flights.id
          FROM flights
         WHERE origin_airport_id =
               (SELECT airports.id
                  FROM airports
                 WHERE city = 'Fiftyville')
           AND year = 2021
           AND month = 7
           AND day = 29
      ORDER BY hour, minute
         LIMIT 1);

-- find the suspect by matching their phone number, passport number, license plate, account number, and passenger name
SELECT name
  FROM people
 WHERE license_plate IN
       (SELECT license_plate
          FROM bakery_security_logs
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND hour = 10
           AND minute >= 15
           AND minute <= 25
           AND activity = 'exit')
   AND name IN
            (SELECT name
               FROM atm_transactions
                    JOIN bank_accounts
                    ON atm_transactions.account_number = bank_accounts.account_number
                    JOIN people
                    ON bank_accounts.person_id = people.id
              WHERE year = 2021
                AND month = 7
                AND day = 28
                AND atm_location LIKE 'leggett street'
                AND transaction_type = 'withdraw')
   AND phone_number IN
       (SELECT caller
          FROM phone_calls
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND duration < 60)
   AND passport_number IN
       (SELECT DISTINCT(passport_number)
          FROM airports
               JOIN flights
               ON airports.id = flights.origin_airport_id
               JOIN passengers
               ON flights.id = passengers.flight_id
         WHERE flights.id =
               (SELECT flights.id
                  FROM flights
                       JOIN airports
                       ON flights.origin_airport_id
                 WHERE city = 'Fiftyville'
                   AND year = 2021
                   AND month = 7
                   AND day = 29
              ORDER BY hour, minute
                 LIMIT 1));

-- GET CITY
SELECT city FROM airports
       JOIN flights
       ON airports.id = flights.destination_airport_id
 WHERE flights.id =
       (SELECT flights.id
          FROM flights
               JOIN airports
               ON flights.origin_airport_id
          WHERE city = 'Fiftyville'
          AND year = 2021
          AND month = 7
          AND day = 29
     ORDER BY hour, minute
        LIMIT 1);


-- GET ACCOMPLICE
SELECT name
  FROM people
       JOIN phone_calls
       ON people.phone_number = phone_calls.receiver
 WHERE caller =
       (SELECT phone_number
          FROM people
         WHERE name = 'Bruce')
   AND year = 2021
   AND month = 7
   AND day = 28
   AND duration < 60;
