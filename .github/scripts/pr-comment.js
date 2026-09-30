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

  const runUrl = `${context.serverUrl}/${context.repo.owner}/${context.repo.repo}/actions/runs/${context.runId}`;

  let language = GetLanguage(report_name);

  await github.rest.issues.createComment({
    owner: context.repo.owner,
    repo: context.repo.repo,
    issue_number: context.issue.number,
    body: `<!--${report_name}Comment--> 
# ${language} Unit Test
![Test count](https://img.shields.io/badge/test-${jsonObj.testsuites[0]["@_tests"]}-grey?style=for-the-badge)

[Voir le run](${runUrl})`,
  });
};

function GetLanguage(report_name) {
  switch (report_name) {
    case 'cpp-result': return 'CPP';    
    case 'go-result': return 'Go';    
    default: return 'None';
  }
}
