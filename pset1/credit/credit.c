#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long card_number = get_long("Enter credit card number: ");  // Get credit card number
    long digits = card_number;                                  // Store the digits when looping through the credit card number
    int sum_digits = 0;                                   // The sum of the products' digits and the other digits
    string card_type = "INVALID\n";                             // Store the card type. INVALID by default
    int digit_counter = 0;                                      // Count the amount of digits when looping through the card number
    
    // Loop through the credit card number
    while (digits != 0)
    {
        // Check for starting digit(s) and set card type accordingly
        switch (digits)
        {
            case 4:
                card_type = "VISA\n";
                break;
            case 34:
            case 37:
                card_type = "AMEX\n";
                break;
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
                card_type = "MASTERCARD\n";
                break;
        }
        
        // Add non-multiplied digit to the sum, remove digit from digits and increase counter by 1
        sum_digits += (digits % 10); 
        digits -= (digits % 10);
        digits /= 10;
        digit_counter++;
        
        // Check for starting digit(s) and set card type accordingly
        switch (digits)
        {
            case 4:
                card_type = "VISA\n";
                break;
            case 34:
            case 37:
                card_type = "AMEX\n";
                break;
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
                card_type = "MASTERCARD\n";
                break;
        }

        // If digits not equal to 0 add the product's digits to sum, remove digit from digits and increase counter by 1
        if (digits != 0)
        {
            int multiplied = (digits % 10) * 2;
            int digit1 = (multiplied % 10);
            multiplied /= 10;
            int digit2 = (multiplied % 10);
            sum_digits += (digit1 + digit2);
            digits -= (digits % 10);
            digits /= 10;
            digit_counter++;
        }
        
    }
    
    // If the last number of the sum is 0, check length of card number. Else, print INVALID.
    if ((sum_digits % 10) == 0)
    {
        // If length is 13, 15 or 16, print card type which was set previously depending on starting digit(s). Else, print INVALID.
        switch (digit_counter)
        {
            case 13:
            case 15:
            case 16:
                printf("%s", card_type);
                break;
            default:
                printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}