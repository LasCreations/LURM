import User from '../modules/user.js'
import { getInstitutions, getDegrees } from '../fetchAPI/institutions.js';


export function createSignUpForm() {
    //Use const as global variables then break up code into functions
    //IE add listeners
    //Add ID
    //Add Text Context etc etc

    const form = document.createElement('form');
    form.id = 'signupForm';
    form.enctype = 'multipart/form-data'

    //Username label
    const usernameLabel = document.createElement('label');
    usernameLabel.for = 'username';
    usernameLabel.textContent = 'Username:';
    form.appendChild(usernameLabel);

    //Username input
    const usernameInput = document.createElement('input');
    usernameInput.type = 'text';
    usernameInput.id = 'username';
    usernameInput.name = 'username';
    form.appendChild(usernameInput);

    //Password label
    const passwordLabel = document.createElement('label');
    passwordLabel.for = 'password';
    passwordLabel.textContent = 'Password:';
    form.appendChild(passwordLabel);

    //Password input
    const passwordInput = document.createElement('input');
    passwordInput.type = 'password';
    passwordInput.id = 'password';
    passwordInput.name = 'password';
    form.appendChild(passwordInput);

    // College/University Label
    const institutionsLabel = document.createElement('label');
    institutionsLabel.for = 'institutionSelect';
    institutionsLabel.textContent = 'College/University';
    form.appendChild(institutionsLabel);

    // College/University Select
    const institutionSelect = document.createElement('select');
    institutionSelect.id = 'institutionSelect';
    institutionSelect.name = 'institutionSelect';

    //Add an empty value
    const option = document.createElement('option');
    option.value = " ";
    option.text = " ";
    institutionSelect.appendChild(option);

    getInstitutions(institutionSelect);
    form.appendChild(institutionSelect);

    // Degree Label
    const degreeLabel = document.createElement('label');
    degreeLabel.for = 'degreeSelect';
    degreeLabel.textContent = 'Degree';
    form.appendChild(degreeLabel);

    // Degree Select
    const degreeSelect = document.createElement('select');
    degreeSelect.id = 'degreeSelect';
    degreeSelect.name = 'degreeSelect';
    form.appendChild(degreeSelect);

    institutionSelect.addEventListener('change', function () {
        getDegrees(institutionSelect.value, degreeSelect)
    });


    const imageInput = document.createElement('input');
    imageInput.type = 'file';
    imageInput.id = 'imageInput';
    imageInput.accept = 'image/*'; //ask user to upload jpeg
    form.appendChild(imageInput);

    // Submit button
    const submitButton = document.createElement('button');
    submitButton.type = 'submit'; // Use 'button' to prevent form submission for this example
    submitButton.textContent = 'Signup';
    // submitButton.addEventListener('click', handleSignUp);
    submitButton.addEventListener('click', uploadImage);
    form.appendChild(submitButton);

    // Append the form to the 'app' div
    document.getElementById('signUpForm-container').appendChild(form);
}

function handleSignUp() {

    const username = document.getElementById('username').value;
    const password = document.getElementById('password').value;

    console.log('Login clicked with username:', username, 'and password:', password);
}