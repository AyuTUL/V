<?php
require_once '../config.php';
requireAdmin();
$activePage = 'questions';
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Quiz Questions — Admin</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link href="https://fonts.googleapis.com/css2?family=Oswald:wght@400;600;700&family=Barlow:wght@300;400;500&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="../css/admin.css">
</head>
<body>

<?php include 'sidebar.php'; ?>

<div class="main">
    <div class="page-header">
        <h1>🧠 QUIZ QUESTIONS</h1>
        <p>Manage football quiz questions shown as lifelines on missed shots</p>
    </div>

    <!-- ADD FORM -->
    <div class="card">
        <div class="card-header">
            <span class="card-title" id="form-title">ADD NEW QUESTION</span>
        </div>
        <div class="card-body">
            <div id="form-alert"></div>
            <div class="form-grid">
                <div class="field-group">
                    <label>QUESTION</label>
                    <textarea id="f-question" rows="3" placeholder="e.g. How many players are on a football team?"></textarea>
                </div>
                <div class="form-row">
                    <div class="field-group">
                        <label>OPTION A</label>
                        <input type="text" id="f-a" placeholder="Answer A">
                    </div>
                    <div class="field-group">
                        <label>OPTION B</label>
                        <input type="text" id="f-b" placeholder="Answer B">
                    </div>
                    <div class="field-group">
                        <label>OPTION C</label>
                        <input type="text" id="f-c" placeholder="Answer C">
                    </div>
                    <div class="field-group">
                        <label>OPTION D</label>
                        <input type="text" id="f-d" placeholder="Answer D">
                    </div>
                </div>
                <div class="field-group" style="max-width:200px">
                    <label>CORRECT ANSWER</label>
                    <select id="f-correct">
                        <option value="a">A</option>
                        <option value="b">B</option>
                        <option value="c">C</option>
                        <option value="d">D</option>
                    </select>
                </div>
                <div style="display:flex;gap:10px;align-items:center">
                    <button class="btn-primary" onclick="submitForm()">SAVE QUESTION</button>
                    <button class="btn-danger" onclick="resetForm()" id="cancel-btn" style="display:none">CANCEL</button>
                    <input type="hidden" id="edit-id" value="">
                </div>
            </div>
        </div>
    </div>

    <!-- QUESTIONS LIST -->
    <div class="card">
        <div class="card-header">
            <span class="card-title">ALL QUESTIONS (<span id="q-count">0</span>)</span>
            <button class="btn-primary" onclick="loadQuestions()" style="font-size:12px;padding:8px 16px">↺ REFRESH</button>
        </div>
        <div style="overflow-x:auto">
            <table class="admin-table">
                <thead>
                    <tr>
                        <th style="width:40px">#</th>
                        <th>QUESTION</th>
                        <th>A</th><th>B</th><th>C</th><th>D</th>
                        <th>ANSWER</th>
                        <th>ACTIONS</th>
                    </tr>
                </thead>
                <tbody id="questions-tbody">
                    <tr><td colspan="8" style="text-align:center;color:var(--muted);padding:24px">Loading...</td></tr>
                </tbody>
            </table>
        </div>
    </div>
</div>

<!-- DELETE CONFIRM MODAL -->
<div class="modal-overlay" id="delete-modal">
    <div class="modal-box">
        <div class="modal-title">🗑️ DELETE QUESTION?</div>
        <p style="color:var(--muted);font-size:14px">This action cannot be undone.</p>
        <div class="modal-actions">
            <button class="btn-danger" onclick="closeDeleteModal()" style="padding:10px 20px">CANCEL</button>
            <button class="btn-primary" id="confirm-delete">DELETE</button>
        </div>
    </div>
</div>

<script>
let questions = [];
let deleteId  = null;

async function loadQuestions() {
    const res  = await fetch('../api/admin.php?action=get_questions');
    const data = await res.json();
    questions  = data.questions || [];
    document.getElementById('q-count').textContent = questions.length;

    const tbody = document.getElementById('questions-tbody');
    if (!questions.length) {
        tbody.innerHTML = '<tr><td colspan="8" style="text-align:center;color:var(--muted);padding:24px">No questions yet. Add some above!</td></tr>';
        return;
    }

    tbody.innerHTML = questions.map((q, i) => `
        <tr id="row-${q.id}">
            <td style="color:var(--muted)">${i+1}</td>
            <td class="q-text" title="${esc(q.question)}">${esc(q.question)}</td>
            <td>${esc(q.option_a)}</td>
            <td>${esc(q.option_b)}</td>
            <td>${esc(q.option_c)}</td>
            <td>${esc(q.option_d)}</td>
            <td><span class="badge badge-correct">${q.correct_answer.toUpperCase()}</span></td>
            <td>
                <button class="btn-edit" onclick="editQuestion(${q.id})">EDIT</button>
                <button class="btn-danger" onclick="showDeleteModal(${q.id})">DELETE</button>
            </td>
        </tr>`).join('');
}

function editQuestion(id) {
    const q = questions.find(x => x.id == id);
    if (!q) return;
    document.getElementById('edit-id').value    = q.id;
    document.getElementById('f-question').value = q.question;
    document.getElementById('f-a').value        = q.option_a;
    document.getElementById('f-b').value        = q.option_b;
    document.getElementById('f-c').value        = q.option_c;
    document.getElementById('f-d').value        = q.option_d;
    document.getElementById('f-correct').value  = q.correct_answer;
    document.getElementById('form-title').textContent = 'EDIT QUESTION #' + id;
    document.getElementById('cancel-btn').style.display = 'inline-block';
    window.scrollTo({ top: 0, behavior: 'smooth' });
}

function resetForm() {
    document.getElementById('edit-id').value    = '';
    document.getElementById('f-question').value = '';
    document.getElementById('f-a').value = document.getElementById('f-b').value = '';
    document.getElementById('f-c').value = document.getElementById('f-d').value = '';
    document.getElementById('f-correct').value  = 'a';
    document.getElementById('form-title').textContent = 'ADD NEW QUESTION';
    document.getElementById('cancel-btn').style.display = 'none';
    document.getElementById('form-alert').innerHTML = '';
}

async function submitForm() {
    const editId = document.getElementById('edit-id').value;
    const action = editId ? 'update_question' : 'add_question';
    const alertEl = document.getElementById('form-alert');
    alertEl.innerHTML = '';

    const body = new FormData();
    body.append('action', action);
    if (editId) body.append('id', editId);
    body.append('question',      document.getElementById('f-question').value.trim());
    body.append('option_a',      document.getElementById('f-a').value.trim());
    body.append('option_b',      document.getElementById('f-b').value.trim());
    body.append('option_c',      document.getElementById('f-c').value.trim());
    body.append('option_d',      document.getElementById('f-d').value.trim());
    body.append('correct_answer', document.getElementById('f-correct').value);

    const res  = await fetch('../api/admin.php', { method:'POST', body });
    const data = await res.json();

    if (data.success) {
        alertEl.innerHTML = `<div class="alert alert-success">✅ ${data.message}</div>`;
        resetForm();
        loadQuestions();
    } else {
        alertEl.innerHTML = `<div class="alert alert-error">❌ ${data.error}</div>`;
    }
}

function showDeleteModal(id) {
    deleteId = id;
    document.getElementById('delete-modal').classList.add('show');
}
function closeDeleteModal() {
    deleteId = null;
    document.getElementById('delete-modal').classList.remove('show');
}

document.getElementById('confirm-delete').addEventListener('click', async () => {
    if (!deleteId) return;
    const body = new FormData();
    body.append('action', 'delete_question');
    body.append('id', deleteId);
    const res  = await fetch('../api/admin.php', { method:'POST', body });
    const data = await res.json();
    closeDeleteModal();
    if (data.success) loadQuestions();
});

function esc(s) { return String(s).replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;'); }

loadQuestions();
</script>
</body>
</html>
