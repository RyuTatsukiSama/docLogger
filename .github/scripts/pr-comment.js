module.exports = async ({ github, context, core, report }) => {
    let result;
    if ('${{ needs.unit-test.result }}' === 'success') {
        result = '✅'
    } else if ('${{ needs.unit-test.result }}' === 'failure') {
        result = '❌';
    } else {
        result = '❓';
    }

    await github.rest.issues.createComment({
        owner: context.repo.owner,
        repo: context.repo.repo,
        issue_number: context.issue.number,
        body: `${result} ${context.serverUrl}/${context.repo.owner}/${context.repo.repo}/actions/runs/${context.runId}`
    });
}