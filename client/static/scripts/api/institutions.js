export function getInstitutions(institutionSelect) {
    fetch('/institutions').then(res => {
        if (res.ok) {
            console.log("Institutions Data recieved");
            return res.json();
        } else {
            console.log("Institutions Data not recieved");
            throw new Error('Network response was not ok');
        }
    }).then(data => {
        data.forEach(function (currentObject) {
            const option = document.createElement('option');
            option.value = currentObject.name;
            option.text = currentObject.name;
            institutionSelect.appendChild(option);
        });
    }).catch(error => {
        console.error("Error:", error.message);
    });
}