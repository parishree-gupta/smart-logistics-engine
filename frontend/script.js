async function runOptimization() {

    document.getElementById("output").innerText =
        "Sending data to backend...";

    try {

        const response = await fetch(
            "http://127.0.0.1:5000/run",
            {
                method: "POST",
                headers: {
                    "Content-Type": "application/json"
                },
                body: JSON.stringify({
                    test: "hello"
                })
            }
        );

        const result = await response.json();

        document.getElementById("output").innerText =
            JSON.stringify(result, null, 2);

    }
    catch(error) {

        document.getElementById("output").innerText =
            "ERROR:\n" + error;
    }
}

document.getElementById("runBtn")
    .addEventListener("click", runOptimization);