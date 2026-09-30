const fs = require("node:fs");
const { XMLParser, XMLBuilder, XMLValidator } = require("fast-xml-parser");

module.exports = async ({ github, context, core, report_name }) => {
  const data = fs.readFileSync(report_name, "utf8");

  const options = {
    ignoreAttributes : false,
    isArray: (name, jpath, isLeafNode, isAttribute) => { 
        return jpath === 'testsuites' || jpath === 'testsuite';
    }
  };

  const parser = new XMLParser(options);
  let jsonObj = parser.parse(data);
  console.log(jsonObj.root.item[0]["@_tests"]);

  await github.rest.issues.createComment({
    owner: context.repo.owner,
    repo: context.repo.repo,
    issue_number: context.issue.number,
    body: `${result} ${context.serverUrl}/${context.repo.owner}/${context.repo.repo}/actions/runs/${context.runId}`,
  });
};
