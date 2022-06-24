// Array with all the correct answers
const answers = ['Oslo', 'Joe Biden', 'Green', 'Blue'];


function checkAnswer(element) {
        const value = element.value;
        const classList = element.classList; // All the element's classes in a string array
        
        // Loop through all correct answers
        for (i = 0; i < answers.length; i++) {
            // Check if the element has a class equal to 'question1-answer', 'question2-answer' etc.
            if (classList.contains(`question${i+1}-answer`)) {
                // Assign the div element with class for example 'question1-result' to result variable
                const result = document.querySelector(`#question${i+1}-result`);
                // If element value is equal to correct answer, show 'correct' and set colors to green
                // Else show 'incorrect' and set colors to red
                if (value === answers[i]) {
                    result.innerHTML = 'Correct';
                    result.style.color = 'green';
                    element.style.backgroundColor = 'green';
                } else {
                    result.innerHTML = 'Incorrect';
                    result.style.color = 'red';
                    element.style.backgroundColor = 'red';
                };
            };
        };
        
    };
    
// Select all elements with class="click", which is all the buttons
// For each element, add an eventlistener that triggers when the button is clicked on
// When clicked, call checkAnswer with the element that was clicked as an argument
document.querySelectorAll('.click').forEach((element) => {
    element.addEventListener('click', (event) => { checkAnswer(event.target); });
});

// Select all elements with class="change", which is all the text input elements
// For each element, add an eventlistener that triggers when element value is changed
// When changed, call checkAnswer with the element that was changed as an argument
document.querySelectorAll('.change').forEach((element) => {
    element.addEventListener('change', (event) => { checkAnswer(event.target); });
});