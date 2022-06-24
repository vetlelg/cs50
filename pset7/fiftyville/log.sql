-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Get an overview of the crime scene reports
SELECT * FROM crime_scene_reports;

-- Find out what happened in Humphrey street prior and after the incident
SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street";

-- Get an overview of the interviews, because it's mentioned in the crime scene report that interviews has been conducted with three witnesses
SELECT * FROM interviews;

-- Filter by date
SELECT * FROM interviews WHERE month = 7 AND day = 28;

-- Filter by date and transcript that mentions bakery
SELECT * FROM interviews WHERE month = 7 AND day = 28 AND transcript LIKE "%bakery%";

-- Check the bakery security logs as it's mentioned by witness that a car left the bakery shortly after the incident. Not sure what hour/minute the theft occurred
SELECT month, day, hour, minute, activity, license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7;

-- Check atm transactions in Leggett Street on 28th July, as it's mentioned by witness that the thief withdrew money before the theft. Didn't give me much useful information as I don't know the amount withdrew or account number
SELECT * FROM atm_transactions WHERE atm_location = "Leggett Street";

-- Try to find the thief by joining tables of people, atm transactions, bank accounts and bakery security logs, and filtering by date
SELECT * FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.day = 28
AND bakery_security_logs.month = 7
AND atm_transactions.day = 28
AND atm_transactions.month = 7;

-- Filter by atm location as well
SELECT * FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.day = 28
AND bakery_security_logs.month = 7
AND atm_transactions.day = 28
AND atm_transactions.month = 7
AND atm_transactions.atm_location = "Leggett Street";

-- Get an overview of phone calls on 28th July
SELECT * FROM phone_calls WHERE day = 28 AND month = 7;

-- Filter by duration as well
SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND duration < 60;

-- Join phone calls table as well on phone number
SELECT * FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE bakery_security_logs.day = 28
AND bakery_security_logs.month = 7
AND atm_transactions.day = 28
AND atm_transactions.month = 7
AND atm_transactions.atm_location = "Leggett Street"
AND phone_calls.day = 28
AND phone_calls.month = 7
AND phone_calls.duration < 60;

-- Get an overview of the airports table
SELECT * FROM airports;

-- Get an overview of flights from Fiftyville on 29th July and find the earliest flight.
-- Earliest flight has flight ID 36. The destination_airport_id is 4, which is LaGuardia Airport in New York City
SELECT * FROM flights WHERE origin_airport_id = 8 AND day = 29 AND month = 7;

-- Join passengers, flights and airports table as well and filter on flight ID that we got from the previous query. The result is Bruce and Taylor and they arrived and left the bakery approximately the same time.
SELECT * FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
JOIN phone_calls ON phone_calls.caller = people.phone_number
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE bakery_security_logs.day = 28
AND bakery_security_logs.month = 7
AND atm_transactions.day = 28
AND atm_transactions.month = 7
AND atm_transactions.atm_location = "Leggett Street"
AND phone_calls.day = 28
AND phone_calls.month = 7
AND phone_calls.duration < 60
AND flights.id = 36;

-- Find the two people who received the phone calls of Bruce and Taylor. The result is James and Robin.
SELECT * FROM people WHERE phone_number = "(676) 555-6554" OR phone_number = "(375) 555-8161";

-- I now realize that the crime took place at 10:15am and that it is stated in the crime scene report. Since the car left the bakery within 10 minutes it means that Bruce is the thief because he left the bakery at 10:18
-- That means Robin is the accomplice, because he is the receiver of the phone call from Bruce

