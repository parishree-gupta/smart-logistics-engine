from flask import Flask, request, jsonify
from flask_cors import CORS
import subprocess
import os
app = Flask(__name__)
CORS(app)
@app.route("/")
def home():
    return "Smart Logistics Backend Running"

@app.route("/run", methods=["POST"])
def run_engine():
    try:
        data = request.json
        cities = data.get("cities", [])
        roads = data.get("roads", [])
        agents = data.get("agents", [])
        orders = data.get("orders", [])
        # -------------------------------
        # CITY INDEX MAP
        # -------------------------------

        city_index = {}

        for i, city in enumerate(cities):
            city_index[city.strip()] = i

        n = len(cities)

        # -------------------------------
        # BUILD ADJACENCY MATRIX
        # -------------------------------

        matrix = [
            [0 for _ in range(n)]
            for _ in range(n)
        ]

        for road in roads:

            parts = road.split()

            if len(parts) != 3:
                continue

            city1 = parts[0]
            city2 = parts[1]
            distance = int(parts[2])

            u = city_index[city1]
            v = city_index[city2]

            matrix[u][v] = distance
            matrix[v][u] = distance

        # -------------------------------
        # WRITE INPUT.TXT
        # -------------------------------

        input_path = "../cpp_engine/input.txt"

        with open(input_path, "w") as f:

            f.write(str(n) + "\n")

            f.write(
                " ".join(cities)
                + "\n\n"
            )

            for row in matrix:

                f.write(
                    " ".join(
                        map(str, row)
                    )
                    + "\n"
                )

            f.write("\n")

            f.write(
                f"{len(agents)} "
                f"{len(orders)}\n\n"
            )

            # Agents
            for agent in agents:

                parts = agent.split()

                city_name = parts[0]
                capacity = parts[1]

                city_id = city_index[
                    city_name
                ]

                f.write(
                    f"{city_id} "
                    f"{capacity}\n"
                )

            f.write("\n")
            # Orders
            for order in orders:
                parts = order.split()
                city_name = parts[0]
                weight = parts[1]
                deadline = parts[2]
                priority = parts[3]
                city_id = city_index[
                    city_name
                ]
                f.write(
                    f"{city_id} "
                    f"{weight} "
                    f"{deadline} "
                    f"{priority}\n"
                )
        # -------------------------------
        # RUN C++ ENGINE
        # -------------------------------
        exe_path = "../cpp_engine/build/main.exe"
        result = subprocess.run(
            exe_path,
            capture_output=True,
            text=True,
            cwd="../cpp_engine"
        )
        print("STDOUT:")
        print(result.stdout)
        print("STDERR:")
        print(result.stderr)
        return jsonify({
            "output": result.stdout,
            "stderr": result.stderr,
        })
    except Exception as e:
        return jsonify({
            "error": str(e)
        })
if __name__ == "__main__":
    app.run(debug=True)
