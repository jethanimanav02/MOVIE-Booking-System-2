let seats = Array(20).fill(0);
let queue = [];
let bookingId = 1000;

function renderSeats() {
  const grid = document.getElementById("seatGrid");
  grid.innerHTML = "";
  seats.forEach((s, i) => {
    const div = document.createElement("div");
    div.className = "seat " + (s ? "booked" : "available");
    div.onclick = () => selectSeat(i);
    grid.appendChild(div);
    if ((i + 1) % 5 === 0) grid.appendChild(document.createElement("br"));
  });
}

function selectSeat(i) {
  if (seats[i]) return alert("❌ Seat already booked!");
  seats[i] = 1;
  renderSeats();
}

function bookTicket() {
  const movie = document.getElementById("movie").value;
  const date = document.getElementById("date").value;
  const time = document.getElementById("time").value;
  const seatCount = seats.filter(s => s === 1).length;
  if (!seatCount) return alert("Please select at least one seat.");

  bookingId++;
  const total = seatCount * 350;
  queue.push({ id: bookingId, movie, date, time, total });

  document.getElementById("output").innerHTML = `
    <h3>✅ Booking Confirmed</h3>
    <p>ID: ${bookingId}</p>
    <p>Movie: ${movie}</p>
    <p>Seats: ${seatCount}</p>
    <p>Total: Rs. ${total}</p>
  `;
}

function viewQueue() {
  if (!queue.length) {
    document.getElementById("output").innerHTML = "<p>📋 Queue Empty</p>";
    return;
  }
  let html = "<h3>Current Queue</h3><div class='queue'>";
  queue.forEach(q => html += `<p>${q.id} — ${q.movie} (${q.time})</p>`);
  html += "</div>";
  document.getElementById("output").innerHTML = html;
}

function processBooking() {
  if (!queue.length) return alert("⚠️ No bookings pending!");
  const done = queue.shift();
  alert(`✅ Booking ID ${done.id} processed`);
  viewQueue();
}

renderSeats();
