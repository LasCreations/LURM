//Sends user data to server


export function registerUser(user){
    fetch("/register/user", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(user),
    }).then(res => {
        if (res.ok) {
            console.log("Degree Data recieved");
            return res.json(); 
        } else {
            console.log("Degree Data not recieved");
            throw new Error('Network response was not ok');
        }
    }).then(data => {
        addDegreesToADiv(data);
    }).catch(error => {
        console.error("Error:", error.message);
    });
}
