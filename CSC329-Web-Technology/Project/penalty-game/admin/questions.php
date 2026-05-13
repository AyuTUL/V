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
    <title>Quiz Questions | Admin</title>
    <link rel="stylesheet" href="../css/admin.css">
</head>
<body>
<?php include 'sidebar.php'; ?>
<main class="main">
    <div class="page-hd">
        <h1>Quiz Questions</h1>
        <p>Questions used when a player misses and gets a lifeline.</p>
    </div>

    <div class="card">
        <div class="card-hd"><span class="card-hd-title" id="form-title">Add question</span></div>
        <div class="card-body">
            <div id="form-alert" aria-live="polite"></div>
            <div class="form-grid">
                <div class="field">
                    <label for="f-q">Question</label>
                    <textarea id="f-q" rows="3" placeholder="e.g. How many players are on a football team?"></textarea>
                </div>
                <div class="form-2col">
                    <div class="field"><label for="f-a">Option A</label><input type="text" id="f-a"></div>
                    <div class="field"><label for="f-b">Option B</label><input type="text" id="f-b"></div>
                    <div class="field"><label for="f-c">Option C</label><input type="text" id="f-c"></div>
                    <div class="field"><label for="f-d">Option D</label><input type="text" id="f-d"></div>
                </div>
                <div class="field field--compact">
                    <label for="f-correct">Correct Answer</label>
                    <select id="f-correct">
                        <option value="a">A</option><option value="b">B</option>
                        <option value="c">C</option><option value="d">D</option>
                    </select>
                </div>
                <div class="form-actions">
                    <button type="button" class="btn btn-acc" onclick="submitForm()">Save question</button>
                    <button type="button" class="btn btn-ghost" onclick="resetForm()" id="cancel-btn" hidden>Cancel</button>
                    <input type="hidden" id="edit-id">
                </div>
            </div>
        </div>
    </div>

    <section class="section-block" aria-labelledby="question-list-title">
        <div class="section-head">
            <span class="section-title" id="question-list-title">Questions (<span id="q-count">0</span>)</span>
        </div>
        <div class="table-wrap">
            <table class="tbl">
                <caption class="sr-only">All quiz questions, answers, and edit controls</caption>
                <thead><tr>
                    <th>#</th>
                    <th>Question</th>
                    <th>A</th><th>B</th><th>C</th><th>D</th>
                    <th>Ans</th><th>Actions</th>
                </tr></thead>
                <tbody id="q-tbody">
                    <tr><td colspan="8" class="table-empty">Loading...</td></tr>
                </tbody>
            </table>
        </div>
    </section>
</main>

<div class="modal" id="del-modal" role="dialog" aria-modal="true" aria-labelledby="delete-question-title" aria-describedby="delete-question-desc" aria-hidden="true">
    <div class="modal-box">
        <h3 id="delete-question-title">Delete question?</h3>
        <p id="delete-question-desc">This cannot be undone.</p>
        <div class="modal-actions">
            <button type="button" class="btn btn-ghost" onclick="closeModal()">Cancel</button>
            <button type="button" class="btn btn-acc" id="confirm-del">Delete</button>
        </div>
    </div>
</div>

<script>
let questions = [], deleteId = null, lastFocus = null;
const esc = s => String(s).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');

function openModal(id) {
    deleteId = id;
    lastFocus = document.activeElement;
    const modal = document.getElementById('del-modal');
    modal.classList.add('show');
    modal.setAttribute('aria-hidden', 'false');
    document.getElementById('confirm-del').focus();
}

function closeModal() {
    deleteId = null;
    const modal = document.getElementById('del-modal');
    modal.classList.remove('show');
    modal.setAttribute('aria-hidden', 'true');
    lastFocus?.focus?.();
}

document.addEventListener('keydown', e => {
    if (e.key === 'Escape' && document.getElementById('del-modal').classList.contains('show')) {
        closeModal();
    }
});

async function loadQuestions() {
    const d = await fetch('../api/admin.php?action=get_questions').then(r => r.json());
    questions = d.questions || [];
    document.getElementById('q-count').textContent = questions.length;
    const tbody = document.getElementById('q-tbody');
    if (!questions.length) {
        tbody.innerHTML = '<tr><td colspan="8" class="table-empty">No questions yet.</td></tr>';
        return;
    }
    const trunc = (s, n = 55) => s.length > n ? s.slice(0, n) + '...' : s;
    tbody.innerHTML = questions.map((q, i) => `
        <tr>
            <td><span class="table-id">${i + 1}</span></td>
            <td class="q-text" title="${esc(q.question)}">${esc(trunc(q.question))}</td>
            <td class="table-cell-compact">${esc(q.option_a)}</td>
            <td class="table-cell-compact">${esc(q.option_b)}</td>
            <td class="table-cell-compact">${esc(q.option_c)}</td>
            <td class="table-cell-compact">${esc(q.option_d)}</td>
            <td><span class="badge">${q.correct_answer.toUpperCase()}</span></td>
            <td>
                <div class="row-actions">
                    <button type="button" class="btn-edit" onclick="editQuestion(${q.id})">Edit</button>
                    <button type="button" class="btn-del" onclick="openModal(${q.id})">Delete</button>
                </div>
            </td>
        </tr>`).join('');
}

function editQuestion(id) {
    const q = questions.find(x => x.id == id); if (!q) return;
    document.getElementById('edit-id').value = q.id;
    document.getElementById('f-q').value = q.question;
    document.getElementById('f-a').value = q.option_a;
    document.getElementById('f-b').value = q.option_b;
    document.getElementById('f-c').value = q.option_c;
    document.getElementById('f-d').value = q.option_d;
    document.getElementById('f-correct').value = q.correct_answer;
    document.getElementById('form-title').textContent = 'Edit question #' + id;
    document.getElementById('cancel-btn').hidden = false;
    window.scrollTo({ top: 0, behavior: 'smooth' });
    document.getElementById('f-q').focus();
}

function resetForm() {
    ['edit-id', 'f-q', 'f-a', 'f-b', 'f-c', 'f-d'].forEach(id => document.getElementById(id).value = '');
    document.getElementById('f-correct').value = 'a';
    document.getElementById('form-title').textContent = 'Add question';
    document.getElementById('cancel-btn').hidden = true;
    document.getElementById('form-alert').innerHTML = '';
}

async function submitForm() {
    const editId = document.getElementById('edit-id').value;
    const body = new FormData();
    body.append('action', editId ? 'update_question' : 'add_question');
    if (editId) body.append('id', editId);
    body.append('question', document.getElementById('f-q').value.trim());
    body.append('option_a', document.getElementById('f-a').value.trim());
    body.append('option_b', document.getElementById('f-b').value.trim());
    body.append('option_c', document.getElementById('f-c').value.trim());
    body.append('option_d', document.getElementById('f-d').value.trim());
    body.append('correct_answer', document.getElementById('f-correct').value);
    const d = await fetch('../api/admin.php', { method: 'POST', body }).then(r => r.json());
    const alertEl = document.getElementById('form-alert');
    alertEl.innerHTML = d.success
        ? `<div class="alert alert-ok">${d.message}</div>`
        : `<div class="alert alert-err">${d.error}</div>`;
    if (d.success) { resetForm(); loadQuestions(); }
    setTimeout(() => alertEl.innerHTML = '', 3000);
}

document.getElementById('confirm-del').addEventListener('click', async () => {
    if (!deleteId) return;
    const body = new FormData();
    body.append('action', 'delete_question');
    body.append('id', deleteId);
    await fetch('../api/admin.php', { method: 'POST', body });
    closeModal();
    loadQuestions();
});

loadQuestions();
</script>
</body>
</html>
