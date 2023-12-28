-- 1. Display the structure of the database for better understanding
.schema

-- 2. Retrieve information about crime scene reports on Humphrey Street dated July 28, 2021
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

-- 3. View interviews of three witnesses conducted on July 28, 2021, with references to the bakery
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";

-- 4. Fetch specific ATM transactions with provided details on Leggett Street dated July 28, 2021
SELECT * FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

-- 5. Examine security camera footage of the bakery within about a 10-minute timeframe on July 28, 2021
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 30 AND activity = "exit";

-- 6. Identify the owner of license plates captured in the bakery security logs
SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 30 AND activity = "exit");

-- 7. Retrieve phone call records around the time of the robbery on July 28, 2021, with a duration less than 60 seconds
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

-- 8. Identify names matching both license plate owners and callers during the specified bakery security log
SELECT name FROM people WHERE name IN (SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 30 AND activity = "exit")) AND name IN (SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60));

-- 9. Search for common names in ATM transactions, license plate owners, and callers during the specified events
SELECT name FROM people WHERE name IN (SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"))) AND name IN (SELECT name FROM people WHERE name IN (SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 30 AND activity = "exit")) AND name IN (SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)));

-- 10. Retrieve information about the airport in Fiftyville where the thief may attempt to escape
SELECT * FROM airports WHERE city ="Fiftyville";

-- 11. Get the destination ID for the flight scheduled on July 29, 2021, originating from Fiftyville
SELECT * FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city ="Fiftyville") AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1;

-- 12. Gather more information about the destination airport for the mentioned flight
SELECT * FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city ="Fiftyville") AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1);

-- 13. Retrieve information about passengers on the flight scheduled for July 29, 2021, from Fiftyville
SELECT * FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city ="Fiftyville") AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1);

-- 14. Identify names matching between flight passengers and individuals identified in step 9
SELECT name FROM people WHERE name IN (SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1))) AND name IN (SELECT name FROM people WHERE name IN (SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"))) AND name IN (SELECT name FROM people WHERE name IN (SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 30 AND activity = "exit")) AND name IN (SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60))));

-- 15. Determine who the thief (identified in step 14) contacted after the robbery on July 28, 2021
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller = (SELECT phone_number FROM people WHERE name = "Bruce"));
