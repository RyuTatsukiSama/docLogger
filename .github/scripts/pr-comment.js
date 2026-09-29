const fs = require("node:fs");
const { XMLParser, XMLBuilder, XMLValidator } = require("fast-xml-parser");

module.exports = async ({ github, context, core, report_name }) => {
  const data = fs.readFileSync(report_name, "utf8");
  console.log(data);

  const parser = new XMLParser();
  let jsonObj = parser.parse(data);
  console.log(jsonObj);

  await github.rest.issues.createComment({
    owner: context.repo.owner,
    repo: context.repo.repo,
    issue_number: context.issue.number,
    body: `${result} ${context.serverUrl}/${context.repo.owner}/${context.repo.repo}/actions/runs/${context.runId}`,
  });
};
